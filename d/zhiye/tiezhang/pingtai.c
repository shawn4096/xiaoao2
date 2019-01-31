// Room: /u/zqb/tiezhang/pingtai.c

inherit ROOM;
string look_ditu();
void create()
{
	set("short", "ɽ��ƽ̨");
	set("long", @LONG
������ɽ���һ��ƽ�ء�ɽ�������￪ʼ��֧����������ǰ������������
���Ƶ�ɽ�壬�����˵���ָ��������ɽ��֮���ɴ˶��á������ͬ ����ɽ����
Ĵָ��֮��ΰ��ʳָ��֮�վ�����ָ��֮���ʣ�������֮������Сָ��֮������
�������ɫ������ʤ������ƽ̨һ��Ĵ�ʯ�ϣ�����һ����ͼ(ditu)��
LONG
	);

	set("item_desc", ([ 
"ditu" : (: look_ditu :),
]));

	set("exits", ([ 
"westup" : __DIR__"shanlu-5",
"northeast" : __DIR__"shangu-1",
"eastup" : __DIR__"sslu-1",
"southdown" : __DIR__"shanlu-4",
"northwest" : __DIR__"hclu",
"northup" : __DIR__"shanlu-6",
]));

    set("objects", ([ 
__DIR__"npc/huiyi" : 3,
]));

	set("no_clean_up", 0);
	set("outdoors", "tiezhang");

	set("coor/x",-330);
  set("coor/y",-200);
   set("coor/z",30);
   setup();
	
}

string look_ditu()
{
    return
    "\n"
    "############################\n"
    "#          ��ָ��          #\n"
    "#            ||            #\n"
    "#    ������  ||  ʳָ��    #\n"
    "#         \\ || //         #\n"
    "#          \\||//          #\n"
    "# Сָ��====ƽ̨====Ĵָ�� #\n"
    "############################\n";
}