type decoder('item) = Js.Json.t => 'item;

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

}, "software-factory/cauth"
  ]
}
|};

// Do not handle other potential fields as not needed for our main usage
type sourceRepository = {
  name: string,
  connection: option(string),
};

type project = {
  name: option(string),
  description: string,
  tenant: option(string),
  connection: option(string),
  website: option(string),
  documentation: option(string),
  issue_tracker_url: option(string),
  review_dashboard: option(string),
  mailing_lists: option(list(string)),
  contacts: option(list(string)),
  source_repositories: list(sourceRepository),
  options: option(list(string)),
};

module SRDecode = {
  open Json.Decode;
  let connection = field("connection", string);
  let obj = dict(connection);
};

let decodeSourceRepositoryDict = (name: Js.Dict.key, json: Js.Json.t) => {
  Json.Decode.{
    name,
    connection: json |> field("connection", optional(string)),
  };
};

let debug = (msg, obj) => {
  Js.log("# " ++ msg);
  Js.log(obj);
};

let decodeFail = msg => Json.Decode.DecodeError(msg) |> raise;

// let decodeSourceRepository = (json: Js.Json.t): sourceRepository => {
let decodeSourceRepository: decoder(sourceRepository) =
  json => {
    switch (Js.Json.decodeObject(json)) {
    | Some(dict) =>
      switch (Js.Dict.entries(dict) |> Belt.List.fromArray) {
      | [(k, v)] => decodeSourceRepositoryDict(k, v)
      | _ =>
        "SourceRepository dictionary can only contain one value" |> decodeFail
      }
    | None => Json.Decode.{name: json |> string, connection: None}
    };
  };

/*  let connection =
        json
        |> Json.Decode.optional(
             Json.Decode.at([srdictKey0], SRDecode.connection),
           );
      {name: srdictKey0, connection};
    };
    */
let parseProject = json => {
  let data = Json.parseOrRaise(json);
  Json.Decode.{
    name: data |> optional(field("name", string)),
    description: data |> field("description", string),
    tenant: data |> optional(field("tenant", string)),
    connection: data |> optional(field("connection", string)),
    website: data |> optional(field("website", string)),
    documentation: data |> optional(field("documentation", string)),
    issue_tracker_url: data |> optional(field("issue-tracker-url", string)),
    review_dashboard: data |> optional(field("review-dashboard", string)),
    mailing_lists: data |> optional(field("mailing-lists", list(string))),
    contacts: data |> optional(field("contacts", list(string))),
    source_repositories:
      data |> field("source-repositories", list(decodeSourceRepository)),
    options: data |> optional(field("options", list(string))),
  };
};

let runExample = () => {
  let demo = parseProject(example);
  Js.log(demo.source_repositories |> Belt.List.toArray);
};
