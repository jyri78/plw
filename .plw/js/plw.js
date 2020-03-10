/* PLW.JS 1.0 by jyri78 */
/* NB! This script is not 100% checked, it may contain errors. */

"use strict";
var plw = {};
plw.$ = function(o){return document.getElementById(o);}

/* Based on MDN Tutorial;
   more: https://developer.mozilla.org/en-US/docs/Web/API/XMLHttpRequest/Using_XMLHttpRequest
*/
if (!XMLHttpRequest.prototype.sendAsBinary) {
    XMLHttpRequest.prototype.sendAsBinary = function(sData) {
        var nBytes = sData.length, ui8Data = new Uint8Array(nBytes);
        for (var nIdx = 0; nIdx < nBytes; nIdx++) {
            ui8Data[nIdx] = sData.charCodeAt(nIdx) & 0xff;
        }
        /* send as ArrayBufferView...: */
        this.send(ui8Data);
        /* ...or as ArrayBuffer (legacy)...: this.send(ui8Data.buffer); */
    };
}
plw.AJAXSubmit = (function(){

    function submitData (oData) {
        /* the AJAX request... */
        var oAjaxReq = new XMLHttpRequest();
        oAjaxReq.submittedData = oData;
        oAjaxReq.onload = oData.success;

        /* Here we allow only POSTing data */
        oAjaxReq.open("post", oData.receiver, true);
        if (oData.technique === 3) {
            /* enctype is multipart/form-data */
            var sBoundary = "---------------------------" + Date.now().toString(16);
            oAjaxReq.setRequestHeader("Content-Type", "multipart\/form-data; boundary=" + sBoundary);
            oAjaxReq.sendAsBinary("--" + sBoundary + "\r\n" +
                    oData.segments.join("--" + sBoundary + "\r\n") + "--" + sBoundary + "--\r\n");
        } else {
            /* enctype is application/x-www-form-urlencoded or text/plain */
            oAjaxReq.setRequestHeader("Content-Type", oData.contentType);
            oAjaxReq.send(oData.segments.join(oData.technique === 2 ? "\r\n" : "&"));
        }
    }
    
    function processStatus (oData) {
        if (oData.status > 0) { return; }
        /* the form is now totally serialized! do something before sending it to the server... */
        /* doSomething(oData); */
        /* console.log("AJAXSubmit - The form is now serialized. Submitting..."); */
        submitData (oData);
    }
    
    function pushSegment (oFREvt) {
        this.owner.segments[this.segmentIdx] += oFREvt.target.result + "\r\n";
        this.owner.status--;
        processStatus(this.owner);
    }
    
    function plainEscape (sText) {
        /* How should I treat a text/plain form encoding?
           What characters are not allowed? this is what I suppose...: */
        /* "4\3\7 - Einstein said E=mc2" ----> "4\\3\\7\ -\ Einstein\ said\ E\=mc2" */
        return sText.replace(/[\s\=\\]/g, "\\$&");
    }
    
    function SubmitRequest (oTarget, fSuccess) {
        var nFile, sFieldType, oField, oSegmReq, oFile;

        this.contentType = oTarget.enctype
                ? oTarget.enctype : "application\/x-www-form-urlencoded";
        this.technique = this.contentType === "multipart\/form-data"
                ? 3 : this.contentType === "text\/plain" ? 2 : 1 /*: 0*/;
        this.receiver = oTarget.action;
        this.status = 0;
        this.segments = [];
        this.success = fSuccess;

        var fFilter = this.technique === 2 ? plainEscape : escape;
        for (var nItem = 0; nItem < oTarget.elements.length; nItem++) {
            oField = oTarget.elements[nItem];
            if (!oField.hasAttribute("name")) { continue; }
            sFieldType = oField.nodeName.toUpperCase() === "INPUT"
                    ? oField.getAttribute("type").toUpperCase() : "TEXT";
            if (sFieldType === "FILE" && oField.files.length > 0) {
            if (this.technique === 3) {
                /* enctype is multipart/form-data */
                for (nFile = 0; nFile < oField.files.length; nFile++) {
                    oFile = oField.files[nFile];
                    oSegmReq = new FileReader();
                    /* (custom properties:) */
                    oSegmReq.segmentIdx = this.segments.length;
                    oSegmReq.owner = this;
                    /* (end of custom properties) */
                    oSegmReq.onload = pushSegment;
                    this.segments.push("Content-Disposition: form-data; name=\"" +
                            oField.name + "\"; filename=\"" + oFile.name +
                            "\"\r\nContent-Type: " + oFile.type + "\r\n\r\n");
                    this.status++;
                    oSegmReq.readAsBinaryString(oFile);
                }
            } else {
                /* enctype is application/x-www-form-urlencoded or text/plain or
                    method is GET: files will not be sent! */
                for (nFile = 0; nFile < oField.files.length;
                    this.segments.push(fFilter(oField.name) + "=" + fFilter(oField.files[nFile++].name)));
                }
            } else if ((sFieldType !== "RADIO" && sFieldType !== "CHECKBOX") || oField.checked) {
                /* NOTE: this will submit _all_ submit buttons. Detecting the correct one is non-trivial. */
                /* field type is not FILE or is FILE but is empty */
                this.segments.push(
                    this.technique === 3 ? /* enctype is multipart/form-data */
                            "Content-Disposition: form-data; name=\"" + oField.name
                            + "\"\r\n\r\n" + oField.value + "\r\n"
                            : /* enctype is application/x-www-form-urlencoded or text/plain or method is GET */
                            fFilter(oField.name) + "=" + fFilter(oField.value)
                );
            }
        }
        processStatus(this);
    }
    
    return function (oFormElement, fSuccess) {
        if (!oFormElement.action || !fSuccess) { return; }
        new SubmitRequest(oFormElement, fSuccess);
    };
})();