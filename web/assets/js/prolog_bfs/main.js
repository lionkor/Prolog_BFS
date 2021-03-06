/**
 * Array holding all instances of prolog bfs.
 * The "instanceid" is the key of the instance in this array.
 * @TODO: automatically delete old instances to save resources.
 */
var instances = [];


/*
 * Alert on the top right to indicate errors
 */
var alert = new Alert();

/*
 * Used to indicate where in the code a syntax error occured
 */
var syntaxError = new SyntaxError();

/**
 * Used to indicate whether the wasm runtime is initialized
 * and ready to use. Initialization is done in the background
 * automatically.
 * @type Boolean true if the runtime is initialized
 */
var runtimeInitialized = false;

/*
 * This is a container for the emscripten Module that contains
 * the PrologBFSWasmWrapper and other classes. It's set as
 * soon as the web assembly runtime is set up.
 */
var emscriptenModuleInstance;

/*
 * Before an instance of prolog bfs can be created,
 * we need to be sure the wasm runtime is initialized.
 */
(new EmscriptenModule).then(function (Module) {
    console.log("WebAssembly/Emscripten runtime initialized.");
    runtimeInitialized = true;
    emscriptenModuleInstance = Module;
});

/**
 * Scroll to the bottom in the results container. Useful after
 * results were pushed.
 */
function scrollResultsToBottom() {
    var theDiv = document.getElementById("results_container");
    theDiv.scrollTop = theDiv.scrollHeight;
}

/*
 * onclick event of the "run" button.
 * This processes the current program and query input
 * and displays the result.
 */
function onRunClicked() {
    // create new instance and store it globally
    var instance = new InterpreterHandler();
    var instanceid = instance.instanceid;
    instances[instanceid] = instance;

    var inputProgram = ace.edit("program").getValue();
    var inputQuery = ace.edit("query").getValue();

    //load program to the interpreter and run it
    try {
        instances[instanceid].tryExecute(inputProgram, inputQuery);
    } catch (err) {
        alert.show("Error getting result. Probably ran out of memory (infinite loop?). Please close some answers (gray boxes) using the X on the top right to free up memory.");
        console.log(err);
    }
    
    // make sure result is visible
    scrollResultsToBottom();
}

function runTests() {
    // c++ unit tests
    (new emscriptenModuleInstance.Tests()).runCatch();
}

/**
 * Automatically store the program code to prevent
 * data loss when the browser crashes.
 */
function autosave() {
    // Store program code for autosaveCookieLifetime days
    Cookies.set('programcode', ace.edit("program").getValue(), {
        expires: autosaveCookieLifetime,
        sameSite: 'lax'
    });
    Cookies.set('querycode', ace.edit("query").getValue(), {
        expires: autosaveCookieLifetime,
        sameSite: 'lax'
    });
}

/*
 * Before browser/tab is closed, autosave
 */
window.onbeforeunload = function () {
    autosave();
};

/*
 * Call autosave every autosaveInterval seconds
 */
setInterval(function () {
    autosave();
}, autosaveInterval);

/*
 * Make all Bootstrap modals draggable. Specifically helpful when moving the
 * tree view away, so you can still see query or program code.
 * Source: https://stackoverflow.com/questions/12571922/make-bootstrap-twitter-dialog-modal-draggable 
 */
$(".modal-header").on("mousedown", function(mousedownEvt) {
    var $draggable = $(this);
    var x = mousedownEvt.pageX - $draggable.offset().left,
        y = mousedownEvt.pageY - $draggable.offset().top;
    $("body").on("mousemove.draggable", function(mousemoveEvt) {
        $draggable.closest(".modal-content").offset({
            "left": mousemoveEvt.pageX - x,
            "top": mousemoveEvt.pageY - y
        });
    });
    $("body").one("mouseup", function() {
        $("body").off("mousemove.draggable");
    });
    $draggable.closest(".modal").one("bs.modal.hide", function() {
        $("body").off("mousemove.draggable");
    });
});