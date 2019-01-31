// Code of ShenZhou
//lh_book.c
//wsky
#include <ansi.h>
inherit ITEM;

int do_start(object me);


void create()
{
        set_name("黄皮册子", ({ "ce zi", "book" }));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", YEL"这是一本黄皮册子，册子上写着《三连环》三个篆字，左下角署名写着全真长春子。\n"NOR);
                set("material", "paper");
                set("no_drop","这样东西不能离开你。\n");
                set("no_get","这样东西不能离开你。\n");
                set("no_steal", 1);
                set("unique", 1);
        set("treasure",1);
                set("value", 300000);
        }
}

void init()
{
        add_action("do_lingwu","read");
  
}
int do_lingwu(string arg)
{
        object me;
        int cost;
        me=this_player();
         if (me->is_busy())
            return notify_fail("你正忙着呢!\n");
        
        if(arg!=this_object()->query("id")) return notify_fail("你要领悟什么?\n");
        
        if(me->query_skill("quanzhen-jianfa", 1) <100)
            return notify_fail("你的全真剑法不够娴熟，无法领悟要决中的奥妙。\n");
            
        if(me->query_skill("taoism",1)<100)
        	return notify_fail("你的道学修为不够。\n");
        	
        if(me->query_skill("literate",1)<100)
        	return notify_fail("你文学水平太差，看不懂此册。\n");
        
        if(this_object()->query("player_id")!=me->query("id"))
        {
                me->add("max_neili",-10);
                return notify_fail(HIR"你一读之下只觉浑身燥热，内力不聚，说不出的难受。\n"NOR);

	}

        if(me->query("quest/quanzhen/sword/lianhuan")==1)
                    return notify_fail("你已经领悟三连环精要。\n");
        
        if(me->query("neili")<1000||me->query("jing")<200)
                return notify_fail("你精神不佳，无法领悟心法中的奥妙。\n");
                
        cost=me->query("int");
        
        if(cost>=30)
                cost=5;
        else
                cost=35-cost;
        
        me->set_temp("lianhuan_cost",cost);
        
        message_vision(YEL"$N从怀中摸出一本小册子,全神灌注地阅读着，不时左手轻轻的比划。\n" NOR, me);
    	me->start_busy((: do_start:));
        return 1;

}

int do_start(object me)
{

        if(me->query_temp("lianhuan_cost")<=0)
        {
                if(random(me->query("int"))>26 && random(me->query("kar"))>26)     
                {
                        me->add("lingwu_lianhuan",1);
                        tell_object(me,HIY"你静坐良久，似乎对三连环的运用有一丝领悟。\n"NOR);
                        
                        if(random(me->query("lingwu_lianhuan"))>=20)
                        {
                                tell_object  (me,HIG"恭喜，你终于领悟出〖三连环〗秘决的精要。\n"NOR);
                                me->set("quest/quanzhen/sword/lianhuan",1);
                                me->delete("lingwu_lianhuan");
                                
                        }
                        me->set("neili",0);
                        me->set("jingli",0);
        
                }
                else
                {
                        
                        tell_object  (me,HIR"你左思右想始终不能领悟d，不由得心中大燥。\n"NOR);
                        me->add("neili", -me->query("max_neili")/20 );
                        me->receive_damage("jing", me->query("max_jing")/20 );
                    	
                    	if(me->query("neili")<0 || me->query("jing")<0)
                    		me->unconcious();
                   		
        	}
        
        	return 0;
        }
        me->add_temp("lianhuan_cost",-1);
        
        return 1;
}
