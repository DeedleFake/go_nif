defmodule Mix.Tasks.CompileNifs do
  use Mix.Task

  @impl true
  def run([]) do
    output = Path.join([:code.priv_dir(:go_nif), "nifs", "go_nif.so"])

    System.find_executable("go")
    |> System.cmd(["build", "-v", "-buildmode=c-shared", "-o", output, "./native"])
  end
end
