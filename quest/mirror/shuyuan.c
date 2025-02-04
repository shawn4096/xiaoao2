// Room: /d/city/shuyuan.c

inherit ROOM;

void create()
{
	set("short", "书院");
	set("long", @LONG
这里是书院的讲堂，窗明几净，一尘不染。一位庄重严肃的老者坐在太师
椅上讲学，那就是当今大儒朱先生了。在他的两侧坐满了求学的学生。一张古
意盎然的书案放在朱先生的前面，案上摆着几本翻开了的线装书籍。朱先生的
身后是一个书架(shujia)讲堂内多历代楹联石刻，足见书院历史的悠久。值得
一提的是嵌在讲堂前左壁的学规(xuegui)。书院老夫子刚奉了圣旨颁发学位，
就在门口树着书院新立的学位公告板(board)。
LONG );
	set("item_desc", ([ /* sizeof() == 1 */
		"xuegui": "
		日讲经书三起，日看纲目数页。
		通晓时务物理，参读古文诗赋。
		读书必须过笔，会课按时蚤完。
		夜读仍戒晏起，疑误定要力争。

	               知识无价。\n",
		"shujia":"一个一尘不染的书架。\n",
		"board": "
       本书院奉圣上恩旨自即日起封授学位：
\n" 
	]));
	set("exits", ([ /* sizeof() == 2 */
		"north"    : __DIR__"shuyuan2",
		"south" : __DIR__"dongdajie1",
	]));

	setup();
}
int valid_leave(object me, string dir)
{
        if (dir == "north" && (userp(me) && !wizardp(me)))
                return notify_fail("那是朱熹的私人寝室！！\n");
        return 1;
}

//是镜像
int is_mirror() { return 1; }