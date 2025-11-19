defmodule GoNif do
  @on_load :init
  @nifs [add: 2]

  defp init() do
    :ok = :erlang.load_nif("./go_nif", 0)
  end

  def add(_, _), do: :erlang.nif_error(:not_loaded)
end
