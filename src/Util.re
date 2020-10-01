


[@bs.val] external __dirname: string = "__dirname";
let getAbsolutePath = (path: string) => {
  Node.Path.resolve(__dirname, path);
};

let printDir = (dirPath: string) => {
  let absolutePath = getAbsolutePath(dirPath);
  let options = Fs.readdirSyncOptions(~withFileTypes=true, ());

  Fs.readdirSync(absolutePath, options)
  |> Array.to_list
  |> List.iter((item: Fs.dirent) => {
       let prefix = item##isDirectory() ? {js|📁|js} : {js|📄|js};
       Js.log(prefix ++ " " ++ item##name);
     });
};


// Error: caml_ml_open_descriptor_in not polyfilled by BuckleScript yet
// let openFile = (path: string) => {
//   let absolutePath = getAbsolutePath(path)
//   Pervasives.open_in(absolutePath)
// }

// let readFile = (path: string) => {
//   let channel = openFile(path)
//   Pervasives.input_line(channel)
// }

let readFile = (path: string) => {
  let absolutePath = getAbsolutePath(path);
  Node.Fs.readFileSync(absolutePath, `utf8)
}

type project = {
  name: string,
}

let decodeJSON = (data: string) => {
  let data = Json.parseOrRaise(data)
  Json.Decode.{
    name: data |> field("name", string)
  }
}
