// /clone/board/worker1_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("���齻����", ({ "board" }) );
        set("location", "/d/city/jiaoliushi");
        set("board_id", "worker_b");
        set("long", "���ǹ���ҽ������쾭���������Ʒ�����԰棬�����BUGҲ���������������\n" );
        setup();
        set("capacity", 100);
}
