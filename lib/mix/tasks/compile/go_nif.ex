defmodule Mix.Tasks.Compile.GoNif do
  use Mix.Task.Compiler

  @output_dir Path.join(:code.priv_dir(:go_nif), "nifs")

  @impl true
  def run([]) do
    output = Path.join(@output_dir, "go_nif.so")

    System.find_executable("go")
    |> System.cmd(["build", "-v", "-buildmode=c-shared", "-o", output, "./native"])
    |> case do
      {_, 0} -> :ok
      {output, _} -> {:error, output}
    end
  end

  @impl true
  def clean() do
    ["go_nif.so", "go_nif.h"]
    |> Enum.map(&Path.join(@output_dir, &1))
    |> Enum.each(&File.rm!/1)

    :ok
  end
end
