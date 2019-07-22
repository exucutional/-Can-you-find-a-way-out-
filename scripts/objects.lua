objects = {}
setting = {
    type = {
        player = 0;
        ball = 1
    };
    type_max = 2;
    repulsion_rate = 50
}
objlist = {
    player = {
        type = setting.type.player;
        animation = {
            "animation_player_down";
            "animation_player_up";
            "animation_player_left";
            "animation_player_right"
        }
    };
    ball = {
        type = setting.type.ball;
        animation = {
            "animation_ball"
        }
    }
}
return objects