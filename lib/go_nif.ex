defmodule GoNif do
  @on_load :init
  @nifs [get: 1]

  defp init() do
    :ok =
      Path.join([:code.priv_dir(:go_nif), "nifs", "go_nif"])
      |> :erlang.load_nif(0)
  end

  def get(_), do: :erlang.nif_error(:not_loaded)
end
