defmodule Advent do
  def check(word1, word2) do
    check(to_charlist(word1), to_charlist(word2), '', 0)
  end

  def check(_, _, _, diff) when diff >= 2 do
    :mismatch
  end

  def check([], [], common, 1) do
    {:match, Enum.reverse(common)}
  end

  def check([w | ord1], [w | ord2], common, diff) do
    check(ord1, ord2, [w | common], diff)
  end

  def check([w1 | ord1], [w2 | ord2], common, diff) do
    check(ord1, ord2, common, diff + 1)
  end
end

words = File.stream!("input") |> Enum.to_list()

words
|> Enum.reduce_while(:mismatch, fn word1, _ ->
  case Enum.reduce_while(words, :mismatch, fn word2, acc ->
         if word1 != word2 do
           case Advent.check(word1, word2) do
             {:match, common} -> {:halt, {:match, common}}
             result -> {:cont, result}
           end
         else
           {:cont, acc}
         end
       end) do
    {:match, common} -> {:halt, {:match, common}}
    result -> {:cont, result}
  end
end)
|> IO.inspect()
