// fojing10.c

inherit ITEM;

string* titles = ({
	"维摩经",
	"法华经",
	"华严经",
//	"无量寿经",
//	"大般涅磐经",
//	"阿含经",
//	"金刚经",
//	"波罗蜜多心经",
});

void create()
{
	set_name(titles[random(sizeof(titles))], ({ "shu", "book" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long", "这是一册佛经。\n");
		set("value", 500);
		set("material", "paper");
		set("skill", ([
			"name":	"buddhism",	// name of the skill
			"exp_required":	0,	// minimum combat experience required
			"jing_cost":	10,	// jing cost every time study this
			"difficulty":	10,	// the base int to learn this skill
			"max_skill":	50	// the maximum level you can learn
		]) );
	}
} 
/*
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
        if (arg!="shu" && arg!="book" )
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


		if ((int)me->query_skill("buddhism", 1) > 50 ){
			write("这本书对于你来说已经太肤浅了！\n");
			return 1;
			}
                neili_lost = 5;
                me->receive_damage("jing", 10,"不明原因");
                me->improve_skill("buddhism", (int)me->query_int()/3);
                write("你正在研习禅宗心法经书，似乎有点心得。\n");
                return 1;

}
*/