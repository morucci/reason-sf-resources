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
  options: option(list(string))
};

module SRDecode = {
  open Json.Decode;
  let connection = field("connection", string);
  let tt = field("zuul/exclude-unprotected-branches", bool);
  let obj = dict(connection);
};

// This is misterious
// https://stackoverflow.com/questions/52828145/using-bs-json-to-decode-object-with-dynamic-keys-in-root
let parseSourceRepositories = json => {
  let srdict = json |> SRDecode.obj;
  let srdictKey0 = (srdict |> Js.Dict.keys)[0];
  let connection = json |> Json.Decode.at([srdictKey0], SRDecode.connection);
  let tt = json |> Json.Decode.at([srdictKey0], SRDecode.tt);
  {
    name: srdictKey0,
    connection: connection,
    zuul_exclude_unprotected_branches: tt,
  }
};

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
      data |> field("source-repositories", list(parseSourceRepositories)),
    options: data |> optional(field("options", list(string)))
  };
};

let runExample = () => {
  parseProject(example);
};
