let example = {|
{
  "contacts": [
    "harrymichal@seznam.cz"
  ],
  "description": "Unprivileged development environment",
  "tenant": "local",
  "website": "https://github.com/debarshiray/toolbox",
  "name": "toolbox",
  "source-repositories": [
    {
      "containers/toolbox": {
        "connection": "github.com",
        "zuul/exclude-unprotected-branches": true
      }
    }
  ]
}
|};

type sourceRepository = {
  name: string,
  connection: string,
  zuul_exclude_unprotected_branches: bool,
};

type project = {
  contacts: list(string),
  description: string,
  tenant: string,
  website: string,
  name: string,
  source_repositories: array(sourceRepository),
};

module MyDecode = {
  open Json.Decode;
  let connection = field("connection", string);
  let obj = dict(connection);
};

let parseSourceRepositories = json => {
  let st = Json.stringify(json);
  print_endline("toto" ++ st);
  let a = json |> MyDecode.obj;
  print_endline(Array.get(a |> Js.Dict.keys, 0));
  // let a = json |> Json.Decode.dict(sourceRepository)
  {
    name: "Test SR",
    connection: "github.com",
    zuul_exclude_unprotected_branches: true,
  };
};

let parseProject = json => {
  let data = Json.parseOrRaise(json);
  Json.Decode.{
    name: data |> field("name", string),
    description: data |> field("description", string),
    contacts: data |> field("contacts", list(string)),
    tenant: data |> field("tenant", string),
    website: data |> field("website", string),
    source_repositories:
      data |> field("source-repositories", array(parseSourceRepositories)),
  };
};

module Decode = {
  open Json.Decode;
  let price = field("price", float);
  let obj = dict(price);
};

let data = {| {
  "AAPL": { "price": 217.36 },
  "ABCD": { "price": 240.5 }
} |};

let decodedData = data |> Json.parseOrRaise |> Decode.obj;

let _ = decodedData->(Js.Dict.unsafeGet("AAPL")) |> Js.log;

let runExample = () => {
  parseProject(example);
};
