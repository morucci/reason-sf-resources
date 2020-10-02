let example = {|
{
    "resources": {
        "connections": {
            "github.com": {
                "base-url": "https://github.com",
                "github-app-name": "softwarefactory-project-zuul",
                "github-label": "mergeit",
                "type": "github",
                "name": "github.com"
            },
            "rdoproject.org": {
                "base-url": "https://review.rdoproject.org/r",
                "type": "gerrit",
                "name": "rdoproject.org"
            }
        },
        "projects": {
            "DLRN": {
                "contacts": [
                    "jpena@redhat.com"
                ],
                "description": "DLRN builds and maintains yum repositories following OpenStack uptream commit streams",
                "issue-tracker-url": "https://tree.taiga.io/project/morucci-software-factory",
                "name": "DLRN",
                "review-dashboard": "default",
                "tenant": "local",
                "website": "http://github.com/softwarefactory-project/DLRN",
                "source-repositories": [
                    {
                        "DLRN": {}
                    },
                    {
                        "dlrnapi_client": {}
                    },
                    {
                        "rdo-infra/puppet-dlrn": {
                            "connection": "rdoproject.org",
                            "zuul/include": [
                                "job"
                            ]
                        }
                    },
                    {
                        "rdo-infra/ansible-role-dlrn": {
                            "connection": "rdoproject.org",
                            "zuul/include": []
                        }
                    }
                ]
            },
            "Packit-Service": {
                "contacts": [
                    "jpopelka@redhat.com"
                ],
                "description": "Packit Service",
                "tenant": "packit-service",
                "website": "https://packit.dev",
                "name": "Packit-Service",
                "source-repositories": [
                    {
                        "zuul/zuul-jobs": {
                            "connection": "opendev.org"
                        }
                    },
                    {
                        "packit/packit-service-zuul": {
                            "zuul/config-project": true
                        }
                    },
                    {
                        "packit/dashboard": {}
                    },
                    {
                        "packit/deployment": {}
                    },
                    {
                        "packit/dist-git-to-source-git": {}
                    },
                    {
                        "packit/ogr": {}
                    },
                    {
                        "packit/packit": {}
                    },
                    {
                        "packit/packit-service": {}
                    },
                    {
                        "packit/packit-service-centosmsg": {}
                    },
                    {
                        "packit/packit-service-fedmsg": {}
                    },
                    {
                        "packit/packit.dev": {}
                    },
                    {
                        "packit/requre": {}
                    },
                    {
                        "packit/sandcastle": {}
                    },
                    {
                        "packit/tokman": {}
                    },
                    {
                        "packit/upsint": {}
                    }
                ]
            },
            "toolbox": {
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
        }
    }
}
|};

type resources = {
    connections: Js.Dict.t(string)
}

let parseResources = (json) => {
    let data = Json.parseOrRaise(json)
    Json.Decode.{
        connections: data |> field("connections", Connection.CNXDecode.obj)
    }
}

let runExample = () => {
  parseResources(example);
};
