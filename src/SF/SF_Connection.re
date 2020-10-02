let example = {|
{
    "pagure.io": {
        "base-url": "https://pagure.io",
        "type": "pagure",
        "name": "pagure.io"
    }
}

|};

type connection = {
  name: string,
  connection_type: string,
  base_url: option(string),
};

module CNXDecode = {
  open Json.Decode;
  let connection_type = field("type", string);
  let name = field("name", string);
  let base_url = optional(field("base-url", string));
  let obj = dict(connection_type);
};

let parseConnection = json => {
  let data = Json.parseOrRaise(json);
  let cnxdict = data |> CNXDecode.obj;
  let cnxdictKey0 = (cnxdict |> Js.Dict.keys)[0];
  Json.Decode.{
    name: data |> at([cnxdictKey0], CNXDecode.name),
    connection_type: data |> at([cnxdictKey0], CNXDecode.connection_type),
    base_url: data |> at([cnxdictKey0], CNXDecode.base_url),
  };
};

let runExample = () => {
  parseConnection(example);
};
