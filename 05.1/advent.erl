-module(advent).
-author("Wojciech Geisler").
-export([run/0, run/1]).

make_re() ->
    Pairs = lists:foldl(fun(L, Acc) ->
                        [<<L, (L+32)>>, <<(L+32), L>> | Acc]
                end, [], lists:seq($A, $Z)),
    Regex = lists:join(<<"|">>, Pairs),
    re:compile(unicode:characters_to_binary(["(", Regex, ")"])).


run() ->
    {ok, Input} = file:read_file("input"),
    size(string:trim(run(Input))).

run(String) ->
   {ok, Re} = make_re(),
   run(String, Re).

run(String, Re) ->
    case re:replace(String, Re, <<"">>, [{return, binary}, global]) of
        String -> String;
        NewString ->
            io:format("From ~B bytes to ~B\n", [size(String), size(NewString)]),
            run(NewString, Re)
    end.

