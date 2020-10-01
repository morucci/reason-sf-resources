// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Json = require("@glennsl/bs-json/src/Json.bs.js");
var Caml_array = require("bs-platform/lib/js/caml_array.js");
var Json_decode = require("@glennsl/bs-json/src/Json_decode.bs.js");

var example = "\n{\n  \"contacts\": [\n    \"harrymichal@seznam.cz\"\n  ],\n  \"description\": \"Unprivileged development environment\",\n  \"tenant\": \"local\",\n  \"website\": \"https://github.com/debarshiray/toolbox\",\n  \"name\": \"toolbox\",\n  \"source-repositories\": [\n    {\n      \"containers/toolbox\": {\n        \"connection\": \"github.com\",\n        \"zuul/exclude-unprotected-branches\": true\n      }\n    }\n  ]\n}\n";

function connection(param) {
  return Json_decode.field("connection", Json_decode.string, param);
}

function obj(param) {
  return Json_decode.dict(connection, param);
}

var SRDecode = {
  connection: connection,
  obj: obj
};

function parseSourceRepositories(json) {
  var srdict = Json_decode.dict(connection, json);
  var srdictKey0 = Caml_array.caml_array_get(Object.keys(srdict), 0);
  return {
          name: srdictKey0,
          connection: "github.com",
          zuul_exclude_unprotected_branches: true
        };
}

function parseProject(json) {
  var data = Json.parseOrRaise(json);
  return {
          contacts: Json_decode.field("contacts", (function (param) {
                  return Json_decode.list(Json_decode.string, param);
                }), data),
          description: Json_decode.field("description", Json_decode.string, data),
          tenant: Json_decode.field("tenant", Json_decode.string, data),
          website: Json_decode.field("website", Json_decode.string, data),
          name: Json_decode.field("name", Json_decode.string, data),
          source_repositories: Json_decode.field("source-repositories", (function (param) {
                  return Json_decode.array(parseSourceRepositories, param);
                }), data)
        };
}

function runExample(param) {
  return parseProject(example);
}

exports.example = example;
exports.SRDecode = SRDecode;
exports.parseSourceRepositories = parseSourceRepositories;
exports.parseProject = parseProject;
exports.runExample = runExample;
/* No side effect */
