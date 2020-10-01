let parsedData =
  Util.readFile("./../test-assets/test.json") |> Util.decodeJSON;

// let data = {| {
//   "start": { "x": 1, "y": -4 },
//   "end":   { "x": 5, "y": 8 }
// } |};

Js.log(parsedData.name);
