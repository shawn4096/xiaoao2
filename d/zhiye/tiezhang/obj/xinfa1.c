//tiezhang-xinfa.c 
inherit ITEM;

void create()
{
        set_name("铁掌心法概要(上)", ({ "tiezhang xinfa", "xinfa","shu","book"}));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "这是一本关于铁掌心法秘籍上半部分，乃是入门概要。\n");
                set("unique", 1);
                set("treasure",1);                              
                set("value", 100000);
                set("material", "paper");
                set("skill", 
                ([
                        "name": "tiezhang-xinfa",          // name of the skill
                        "exp_required": 0,      // minimum combat experience required
                        "jing_cost":    30,     // jing cost every time study this
                        "difficulty":   30,     // the base int to learn this skill
                        "max_skill":    100      // the maximum level you can learn
                ]));
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
        if (!(arg=="tiezhang xinfa" ||arg=="book" || arg=="shu"))
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
		if(me->query("family/family_name") != "铁掌帮")
			return notify_fail("你看了半天，什么意思都不懂。\n");
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


		if ((int)me->query_skill("tiezhang-xinfa", 1) > 100 ){
			write("这本书对于你来说已经太肤浅了！\n");
			return 1;
			}
                neili_lost = 5;
                me->receive_damage("jing", 15,"不明原因");
                me->improve_skill("tiezhang-xinfa", (int)me->query_int()/3);
                write("你正在研习铁掌心法的武功秘籍，似乎有点心得。\n");
                return 1;

}
