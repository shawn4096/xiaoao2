// laozi16.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name( "道德经「第十六章」", ({ "jing", "daode jing" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long",
			CYN "\n"
			"\n\t\t\t第十六\n\n"
			"\t致虚极，守静笃。\n"
			"\t万物并作，吾以观复。\n"
			"\t夫物芸芸，各复归其根。归根曰静，静曰复命。复命曰常，知常\n"
			"曰明。不知常，妄作凶。\n"
			"\t知常容，容乃公，公乃全，全乃天，天乃道，道乃久，没身不殆。\n"
			"\n"NOR
		);
		set("value", 500);
		set("material", "paper");
		set("skill", ([
			"name":	"taoism",	// name of the skill
			"exp_required":	0,	// minimum combat experience required
			"jing_cost": 10, 	// jing cost every time study this
			"difficulty":	15,	// the base int to learn this skill
			"max_skill":	100,	// the maximum level you can learn
			"max_skill":	120,	// the maximum level you can learn
		]) );
	}
}
void init()
{
        add_action("do_du", "du");
        add_action("do_du", "study");
}    
int do_du(string arg)
{
        object me = this_player();
        object where = environment(me);
        int dzlevel; 
        int neili_lost;
        if (!(arg=="jing" ||arg=="daode jing" ))
        return 0;

        if (where->query("pigging")){
                write("你还是专心拱猪吧！\n");
                return 1;
        }
        if (me->is_busy()) {
                write("你现在正忙着呢。\n");
                return 1;
        }

        if( me->is_fighting() ) {
                write("你无法在战斗中专心下来研读新知！\n");
                return 1;
        }

        if (!id(arg)) { 
                write("你要读什么？\n");
                return 1;
        }
	
        if( !me->query_skill("literate", 1) ){
                write("你是个文盲，先学点文化(literate)吧。\n");
                return 1;
        }

        if( (int)me->query("jing") < 15 ) {
                write("你现在过于疲倦，无法专心下来研读新知。\n");
                return 1;
        }
        
        if( (int)me->query("neili") < neili_lost) {
                write("你内力不够，无法钻研这么高深的武功。\n");
                return 1;
        }
		if ((int)me->query_skill("taoism", 1) < 100 ){
			write("这本书对于你来说已经太深奥了！\n");
			return 1;
			}

		if ((int)me->query_skill("taoism", 1) > 120 ){
			write("这本书对于你来说已经太肤浅了！\n");
			return 1;
			}
                neili_lost = 10;
                me->receive_damage("jing", 25,"不明原因");
                me->improve_skill("taoism", (int)me->query_int()/3);
                write("你正在研习老子道德经，对于道家心法似乎有点心得。\n");
                return 1;

}

