-module(advent).
-author("Wojciech Geisler").
-export([run/0]).


-define(INPUT, "input").

run() ->
    {ok, Input} = file:read_file(?INPUT),
    Nums = [binary_to_integer(X) || X  <- string:split(string:trim(Input, both), " ", all)],
    read_node(Nums).


-spec read_node([integer()]) -> {Sum :: integer(), [integer()]}.
read_node([Childs, Metas | Rest]) ->
    {Sum, Rest2, Childmap} = lists:foldl(fun(Id, {S, Nums, Acc}) ->
                                                 {S2, R} = read_node(Nums),
                                                 {S + S2, R, Acc#{Id => S2}}
                                         end, {0, Rest, #{}}, lists:seq(1,Childs)),
    Rest3 = lists:sublist(Rest2, Metas + 1, 30000),

    Sum2 = case Childs of
               0 -> lists:sum(lists:sublist(Rest2, Metas));
               _ -> lists:foldl(fun (M, S) ->
                                        maps:get(M, Childmap, 0) + S
                                end, 0, lists:sublist(Rest2, Metas))
           end,
    {Sum2, Rest3}.
