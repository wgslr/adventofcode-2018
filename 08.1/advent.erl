-module(advent).
-author("Wojciech Geisler").
-export([run/0]).



run() ->
    {ok, Input} = file:read_file("input"),
    % io:format("~p", [string:split(string:trim(Input), " ", all)]),
    Nums = [binary_to_integer(X) || X  <- string:split(string:trim(Input, both), " ", all)],
    run(Nums).

run(Nums) ->
    read_node(Nums).

read_node([Childs, Metas | Rest]) ->
    {Sum, Rest2} = lists:foldl(fun(_, {S, Nums}) ->
                                       {S2,R} = read_node(Nums),
                                       {S + S2, R}
                               end, {0, Rest}, lists:seq(1,Childs)),
    {Sum + lists:sum(lists:sublist(Rest2, Metas)), lists:sublist(Rest2, Metas + 1, 30000)}.
