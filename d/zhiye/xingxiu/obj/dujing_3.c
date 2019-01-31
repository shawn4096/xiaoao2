#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(BLU"『星宿毒经〖下册〗』"NOR, ({ "du jing", "jing" }) );
	set_weight(10);
	if( clonep() )
		set_default_object(__FILE__);
	else {
                set("long",
"\n                 『星宿毒经〖下册〗』\n\n"
"　　毒经为星宿宝典，凡以此经及经内所载药物私与他人，即视为欺师灭祖、\n"
"背叛师门。对叛师之徒，虽上天入地，吾弟子必予诛之。外人持有本经者，吾\n"
"弟子见一个杀一个，见十个杀十个，断不容私阅本门宝典者苟存于世。\n\n"
"　　　　　　　　　　　　　　　　　　　　　　　　　　星宿老仙　丁\n"
"【蒙汗药】\n"
"　用法：将药倒入酒水中诱人喝下（pour yao in <容器>）。\n"
"　药性：不致命，可使人昏厥。对内力极强者，药效不显。\n\n"
"【春药】\n"
"　用法：将药倒入酒水中诱人喝下（pour yao in <容器>）。\n"
"　药性：不论男女，服后欲火如焚，可为我所用。\n\n"
"【断肠散】\n"
"　用法：将药倒入酒水中诱人喝下（pour yao in <容器>）。\n"
"　药性：服药后肝肠寸断而亡。对内力强者，药效不显。\n\n"
"【清心散】\n"
"　用法：吞服（eat san）。\n"
"　药性：为本门毒门解药，可解断肠散和星宿毒掌之毒。\n"
"    \n");
		set("value", 50);
		set("material", "paper");
		set("unit", "本");
        set("value", 100000);
        set("unique", 1);
        set("treasure",1);
        set("skill", ([
                        "name":"poison",       // name of the skill
                        "exp_required": 150000, // minimum combat experience required
                                              // to learn this skill.
                        "jing_cost": 45,      // jing cost every time study this
                        "difficulty": 35,     // the base int to learn this skill
                         "min_skill": 100,                      // modify is jing_cost's (difficulty - int)*5%
                        "max_skill": 150,       // the maximum level you can learn
                                              // from this object.
                ]));
	}
	setup();
}
