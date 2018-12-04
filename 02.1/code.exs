defmodule Advent do

  def count(word) do
    Enum.reduce(:erlang.binary_to_list(word), %{}, fn l, acc -> Map.update(acc, l, 1, &(&1 + 1)) end)
  end

  def proc(m, {x2,x3}) do
      x2 = if Enum.any?(m, fn {_, 2} -> true; _ -> false end) do
        x2 + 1
      else
        x2
      end

      x3 = if Enum.any?(m, fn {_, 3} -> true; _ -> false end) do
        x3 + 1
      else
        x3
      end
      {x2, x3}
    end
end


{x2, x3} = File.stream!("input")
|> Stream.map(&Advent.count/1)
#|> Stream.each(&IO.inspect/1)
|> Enum.reduce({0,0}, &Advent.proc/2)

IO.inspect(x2  * x3)
