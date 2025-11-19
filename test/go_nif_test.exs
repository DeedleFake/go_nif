defmodule GoNifTest do
  use ExUnit.Case
  doctest GoNif

  test "greets the world" do
    assert GoNif.hello() == :world
  end
end
