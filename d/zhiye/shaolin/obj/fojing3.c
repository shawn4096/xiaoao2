// fojing21.c
#include <ansi.h>

inherit ITEM;

string* titles = ({

      "摩诃僧诋律"
	
});

void create()
{
	set_name(YEL+titles[random(sizeof(titles))]+NOR, ({ "moheseng diyu","shu", "book" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long", "这是一册厚厚的一摞佛经，一看就是集佛法之大成。\n");
		set("value", 500);
		set("material", "paper");
		set("skill", ([
			"name":	"buddhism",	// name of the skill
			"exp_required":	0,	// minimum combat experience required
			"jing_cost":	25,	// jing cost every time study this
			"difficulty":	30,
			"min_skill":	100,// the base int to learn this skill
			"max_skill":	200	// the maximum level you can learn
		]) );
	}
}
/*
void init()
{
	if( this_player() == environment() )
	{
		add_action("do_tear", "tear");
	}
}

int do_tear(string arg)
{
	object me, bible;
	object where;

	if ( !arg )
	{
		return notify_fail("什么？\n");
	}

	me = this_player();

	if ( arg == "jing" || arg == "shu" || arg == "book" )
	{
		bible = new(CLASS_D("shaolin")+"/obj/book-jiuyang");
		where = environment(me);
		message_vision("$N轻轻地把书撕掉……，突然从书缝中飘落出几页羊皮纸。\n",
			this_player());
		bible->move(file_name(where));
		destruct(this_object());
	}

	return 1;
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
        if (!(arg=="shu" ||arg=="book" ))
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
		if ((int)me->query_skill("buddhism", 1) < 100 ){
			write("这本书对于你来说已经太深奥了！\n");
			return 1;
			}


		if ((int)me->query_skill("buddhism", 1) > 200 ){
			write("这本书对于你来说已经太肤浅了,看了半天都看不懂！\n");
			return 1;
			}
                neili_lost = 10;
                me->receive_damage("jing", 20,"不明原因");
                me->improve_skill("buddhism", (int)me->query_int()/3);
                write("你正在研习禅宗心法经书，似乎有点心得。\n");
                return 1;

}
*/
