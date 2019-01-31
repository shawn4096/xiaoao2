// /clone/board/xueshan_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("血刀门留言板", ({ "board" }) );
        set("location", "/d/xuedao/shandong3");
        set("board_id", "xuedao_b");
        set("long", "这是供血刀门弟子谈经论佛，激荡人生的留言板。\n" );
        setup();
        set("capacity", 60);
}
