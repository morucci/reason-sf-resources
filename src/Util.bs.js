// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Fs = require("fs");
var Json = require("@glennsl/bs-json/src/Json.bs.js");
var List = require("bs-platform/lib/js/list.js");
var Path = require("path");
var $$Array = require("bs-platform/lib/js/array.js");
var Json_decode = require("@glennsl/bs-json/src/Json_decode.bs.js");

function getAbsolutePath(path) {
  return Path.resolve(__dirname, path);
}

function printDir(dirPath) {
  var absolutePath = Path.resolve(__dirname, dirPath);
  var options = {
    withFileTypes: true
  };
  return List.iter((function (item) {
                var prefix = item.isDirectory() ? "📁" : "📄";
                console.log(prefix + (" " + item.name));
                
              }), $$Array.to_list(Fs.readdirSync(absolutePath, options)));
}

function readFile(path) {
  var absolutePath = Path.resolve(__dirname, path);
  return Fs.readFileSync(absolutePath, "utf8");
}

function decodeJSON(data) {
  var data$1 = Json.parseOrRaise(data);
  return {
          name: Json_decode.field("name", Json_decode.string, data$1)
        };
}

exports.getAbsolutePath = getAbsolutePath;
exports.printDir = printDir;
exports.readFile = readFile;
exports.decodeJSON = decodeJSON;
/* fs Not a pure module */