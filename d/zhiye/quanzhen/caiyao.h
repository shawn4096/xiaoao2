// caiyao.h  采药
// sohu@xojh
//全真教入门job

#include <ansi.h>
#include <medical.h> 

void setup_ob(object me,object victiom);

string *herbs = ({
        HERB("chuanbei"),
        HERB("fuling"),
        HERB("gouzhizi"),
        HERB("heshouwu"),
        HERB("huanglian"),
        HERB("jugeng"),
        HERB("jinyinhua"),
        HERB("shengdi"),
});

string *beasts = ({
        "/clone/beast/xbaozi",
        "/clone/beast/bee",
        "/clone/beast/wuya",
        "/clone/beast/yetu",
        "/clone/beast/deer",
        "/clone/beast/monkey",
});


void init()
{
        object ob = this_player();
        add_action("do_search", "bo");
        add_action("do_search", "search");
        
		add_action("do_dig", "wa");
        add_action("do_dig", "dig");
    
        if (interactive(ob))
        {
                ob->delete_temp("herb");
                if (ob->query_temp("qz/caiyao"))
                        set("count",random(4));
        }
}

int do_search(string arg)
{
        object me,ob;
        int power;


        me = this_player();

        if( me->is_fighting() || me->is_busy() )
                return notify_fail("你正忙着。\n");

        if( me->query_temp("herb/got",1) )
                return notify_fail("这里已经找过了，再找也找不出什么了！\n");

        if( !present("yao chu", me) )
                return notify_fail("你没有工具，无法拨开灌木山草寻找草药！\n");

        if( (int)me->query("jing") < 30 )
                return notify_fail("你太累了，先歇息一会儿吧。\n");

        me->add_temp("herb/times", 1);
        me->receive_damage("jing", 5);
        me->start_busy(1+random(2));

        if( query("count") < 1 && (int)me->query_temp("herb/times") > 30 )
                return notify_fail("你把四周的灌木杂草都翻遍了，可是没发现什么，看来这里没指望了！\n");

        message_vision("$N用药锄拨动着四周的灌木杂草，仔细地看有没有草药！\n", me);

        power = (int)me->query_temp("herb/times") * ( me->query("kar")+me->query("int") + me->query("str") )/3;
        power *= query("count");
		//attention,count=0

        if( power/2 + random(power/2) > 100 ) {
                me->set_temp("herb/found", 1);
                message_vision(HIG"\n$N用药锄不断的拨动着四周的山草，忽然发现杂草之中有一株特别的草！\n"NOR, me);
                return 1;
        }

        //经验值100k后出现动物,不杀不让继续
		if ((objectp(ob=present("xiao baozi"))&&ob->query("owner")==me->query("id"))
			||(objectp(ob=present("bee"))&&ob->query("owner")==me->query("id"))
			||(objectp(ob=present("wuya"))&&ob->query("owner")==me->query("id"))
			||(objectp(ob=present("deer"))&&ob->query("owner")==me->query("id"))
			||(objectp(ob=present("monkey"))&&ob->query("owner")==me->query("id")))
		{
			return notify_fail("地上尚有你寻找的小动物，阻碍你继续寻找草药！\n");
		}
        if(random(10)< 3 && (int)me->query("combat_exp") > 100000 )
        {
                ob=new(beasts[random(sizeof(beasts))]);
				ob->set("owner",me->query("id"));
				ob->set("long",ob->query("long")+"这是玩家"+ob->query("name")+"采药时发现的动物！\n");
                ob->move(environment(me));
				
				
                if(ob->query("id")=="xiao baozi") setup_ob(ob,me);
				if (ob->query("owner")==me->query("id"))
				{   
					message_vision(HIR"突然从草丛中惊起一只$N，它大概受了惊吓，发疯似地向$n发起进攻！\n"NOR, ob,me);
  
					ob->kill_ob(me);
					//ob->start_busy(1+random(3));
				}
      
                return 1;
        }
        

        
        if(random(101)==50 && (int)me->query("combat_exp") > 10000)
        {
                message_vision(HIR"\n$N一不小心用力过猛，忽听嘎巴一声，药锄断为两截！\n"NOR, me);
                ob = present("yao chu", me);
                if(ob)destruct(ob);
        }
        return 1;
}

void setup_ob(object me,object victim)
{
        object *inv;
        mapping skill_status;
        string *sname;
        int i, max = 0, max1, j;


        if ( !me->query_temp("copied") ) {
                if ( mapp(skill_status = victim->query_skills()) ) {
                        skill_status = victim->query_skills();
                        sname = keys(skill_status);

                        for(i=0; i<sizeof(skill_status); i++) {
                                if ( skill_status[sname[i]] > max ) max = skill_status[sname[i]];
                        }


                        max1 = (int)max + random(max);

                        //max = (int)max*3/4 + 1 + random((int)max/4);

                        if( victim->query("combat_exp",1) < 10000 ) max1 /= 2;
                        me->set_skill("dodge", max1);
                        me->set_skill("parry", max1 );
                        me->set_skill("force", max1);
        
                        me->set("combat_exp", victim->query("combat_exp",1)+random(victim->query("combat_exp",1)/10));

                        me->set("max_qi", victim->query("max_qi"));
                        me->set("eff_qi", victim->query("max_qi"));
                        me->set("max_jing", victim->query("max_jing"));
                        me->set("eff_jing", victim->query("max_jing"));
                        me->set("qi", me->query("max_qi"));
                        me->set("jing", me->query("max_jing"));
                        me->set("jiali", victim->query("jiali")*3/4);
                        if ( victim->query("max_jingli") > 0 ) {
                                me->set("max_jingli", victim->query("max_jingli"));
                        }
                        else me->set("max_jingli", 500);
                        me->set("jingli", me->query("max_jingli"));

                        me->set("no_sing", 1);
                        me->set_temp("copied", 1);
                }
        }
}

int do_dig(string arg)
{
        object me, ob,herb;
        int exp;
        int pot,shen;

        me = this_player();

        if( me->is_fighting() || me->is_busy() )
                return notify_fail("你正忙着。\n");
        if( !(ob = present("yao chu", me)) )
                return notify_fail("你没有药锄，怎么挖？\n");

        if( (int)me->query("jing") < 25 )
                return notify_fail("你太累了，先歇息一会儿吧。\n");
        
		if (me->query("jingli")<25) return notify_fail("你的体力快耗没了!\n");
		
		me->receive_damge("jingli", 20+random(10));

        me->start_busy(1);

        if( !me->query_temp("herb/found") ) {
                message_vision("$N拿着药锄使劲的挖着土，忽听嘎巴一声，药锄断为两截！\n", me);
                destruct(ob);
                return 1;
        }

        add("count", -1);
        herb = new(herbs[random(sizeof(herbs))]);
        herb->move(me, 1);
        herb->set("player", me->query("id"));
		herb->set("unit", "块");

        message_vision(HIY"$N用药锄小心翼翼的把$n"+HIY"从土中起出！\n"NOR, me,herb);

		if(me->query_temp("qz/caiyao"))
       {
              exp = 10 + random( 10 );
              pot = exp*2/5;
			
               // if (me->query("potential") > me->query_potential_limit())
                 //       pot = 1 + random(2);
                //me->add("combat_exp", exp);
                //me->add("potential", pot);
                //me->add("party/gongji", 5 + random(6));
			shen=40+random(10);
			me->add("shen", shen);
			me->improve_skill("yaozhi",me->query_int());
			//	me->delete_temp("qz/caiyao");
            tell_object(me, HIC "你通过挖药材获得" + exp + "点经验、" + pot + "点潜能和"+shen+"点正神的额外奖励。\n" NOR);
        }

        message_vision(HIR"\n$N兴奋过度，把药锄一甩，忽听嘎巴一声，药锄断为两截！\n"NOR, me);
        destruct(ob);
        me->delete_temp("herb/found");
        me->set_temp("herb/got", 1);
        return 1;
}

