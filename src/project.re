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

module SRDecode = {
  open Json.Decode;
  let connection = field("connection", string);
  let obj = dict(connection);
};

// This is misterious
// https://stackoverflow.com/questions/52828145/using-bs-json-to-decode-object-with-dynamic-keys-in-root
let parseSourceRepositories = json => {
  let srdict = json |> SRDecode.obj;
  let srdictKey0 = Array.get(srdict |> Js.Dict.keys, 0);
  {
    name: srdictKey0,
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


let runExample = () => {
  parseProject(example);
};
