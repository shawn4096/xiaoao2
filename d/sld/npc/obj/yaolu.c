// yaolu.c

#include <ansi.h>

inherit ITEM;

//#define MAXS 2160
#define MAXS 300
void yao_id(string arg,object yao);
void yao_name(string arg,object yao);
void yao_long(string arg,object yao);
int do_fail();
void qiangjie(object me,int i);
void init()
{
        add_action("do_open", "open");
        add_action("do_fang", "fang");

         add_action("do_pour", "pour"); //加水
       add_action("do_close", "close");
        add_action("do_fire", "dianhuo");
        add_action("do_lianyao", "lianyao");
        add_action("do_miehuo", "miehuo");
        add_action("do_kanyao", "kanyao");
        add_action("do_qingsao", "qingsao");

		add_action("do_qu", "qu");
        add_action("do_quyao", "quyao");
       // add_action("do_get","get");
        add_action("do_put","put");
}

void create()
{
        set_name(HIG "药炉" NOR, ({"yao lu","lu"}));
        set_weight(3000000);
		set_max_encumbrance(2000);

		if (clonep())
                set_default_object(__FILE__);
        else {
                      

				set("long",
                "这是一只用来炼药的炉子，可以\n"
				+HIY"打开(open)炉盖、放(fang)药材，加水(pour ),关闭(close)\n"
				+"点火(dianhuo)炉子,炼药(lianyao),取(qu)药材，看(kan)炉子，\n"
				+"取(quyao)药,若炼药失败可以清扫(qingsao)。\n"NOR);
                set("unit", "只");
                set("no_sell",1);
                set("yaocai",0);
                set("zhuyao",0);
                set("location",1);
				set("no_get",1);
				set("no_steal",1);
				set("no_give",1);
        }
}
int is_container() { return 1; }

//抢劫犯出现

void qiangjie(object me,int i)
{
        object xm;
        object ob=this_object();
		int j,skill;
		string *skills;

        if(!ob)
           return;
        
		//me=ob->query("owner");
        me=this_player();
		
		skills=me->query_skill();

		if(!me)
        {
                call_out("destructing", 1, ob); 
                return;
        }
        //if(objectp(xm=me->query_temp("lianyao/rumo")))
          //      destruct(xm);
        
		xm=new("/d/sld/npc/xinmo");
        if(!objectp(xm))
        {
                me->delete_temp("lianyao/rumo");
                call_out("qiangjie",60);
                return;
        }
		if (i>2)
		{
			xm->set("combat_exp",(int)me->query("combat_exp")*3/2);
			skill=me->query("max_pot")-70+random(10);
		}else if (i>1)
		{
			xm->set("combat_exp",me->query("combat_exp"));
			skill=me->query("max_pot")-20;
		}else {
			xm->set("combat_exp",(int)me->query("combat_exp")*2/3);
			skill=me->query("max_pot")-100;
		}
        
        xm->set("str", me->query_str());
        xm->set("int", me->query_int());
        xm->set("con", me->query_con());
        xm->set("dex", me->query_dex()+me->query_dex()/3);
        xm->set("kar", me->query_kar());
        xm->set("max_qi",me->query("max_qi")+me->query("max_qi")/2);
        xm->set("qi",xm->query("max_qi"));
		xm->set("eff_qi",xm->query("max_qi"));

        xm->set("max_jing",me->query("max_jing")+me->query("max_jing")/2);
        xm->set("jing",xm->query("max_jing"));
		xm->set("eff_jing",xm->query("max_jing"));

        xm->set("max_neili",me->query("max_neili"));
        xm->set("neili",xm->query("max_neili")*2);
        xm->set("eff_jingli",me->query("eff_jingli")+me->query("eff_jingli")/3);
        xm->set("jingli",xm->query("eff_jingli")*2);
        xm->set_skill("dodge", me->query_skill("dodge",1)/2+me->query_skill("dodge"));
        xm->set_skill("parry", me->query_skill("parry",1)/2+me->query_skill("parry"));
        xm->set("name",me->name(1)+"的心魔");
        
		//xm->set("id",me->query("id")+"'s xinmo");

		xm->set("long",me->query("long")+"\n这是"+xm->query("name")+"所幻化的心魔！\n");
        xm->set("gender",me->query("gender"));
        xm->set("title", me->query("title"));   
        xm->set("age", me->query("age"));
        xm->set("owner",me);
		/*
		for (j=0;j>=sizeof(skills);j++ )
		{
			xm->set_skill(skills[j],skill);
		}*/
        me->set_temp("lianyao/rumo",xm);
        xm->move(environment(this_object()));
        me->kill_ob(xm);
        xm->kill_ob(me);
        message_vision("$N整日长时间沉浸在药物之中，恍惚间忽然看见$n向$N猛然击来，不由得大吃一惊！\n",me,xm);
		//出现三次后不再出现
		//if (i>2) return;
		//call_out("qiangjie",10+random(10),me,i+1);
		
		return;
}
       
void destructing(object ob)
{
        if(ob)
                destruct(ob);
}
//取药
int do_get(string arg)
{
        string temp,obj;
        object yl;
        object me = this_player();
        object ob=this_object();

        if(arg)
        {
                if(arg=="all" || arg=="ALL")
                        return 1;
				if (!ob->query("lianyao/open"))
				{
					return notify_fail("炉子尚未打开，你如何取东西？\n");
				}
				if(ob==present(arg, environment(ob)))
                {
                        if(query("zhuyao"))
                                return notify_fail("药炉正在熬煮药物，不能搬动正在煮药的炉子。\n");
                }
                else
                {
				if(sscanf(arg,"%s from %s",temp,obj)==2)
                        {
                                if(objectp(yl=present(obj, me))||
                                   objectp(yl=present(obj, environment(me))))
                                {
                                        if(yl==ob)
                                                return notify_fail("只能从药炉里取(qu)东西。\n");
                                }
								//取出一样后要添加标记
                        }
                }
        }
        return 0;
}
//放置药草
int do_put(string arg)
{
        string temp,obj;
        object yl;
        object me = this_player();
	

        if(arg)
        {
                if(sscanf(arg,"%s in %s",temp,obj)==2)
                {
                        if(objectp(yl=present(obj, me))||
                           objectp(yl=present(obj, environment(me))))
                        {
                                if(yl==this_object())
                                        return notify_fail("只能往药炉里放(fang)东西。\n");
                        }
                }
        }
		if (!yl->query("lianyao/open"))
		{
			return notify_fail("炉子尚未打开，你如何取东西？\n");
		}
        return 0;
}
//清扫炉子
int do_qingsao(string arg)
{
	object ob,me;
	me=this_player();
	ob=this_object();
	if (!arg||arg!="lu")
	{
		return notify_fail("你要清扫什么？\n");
	}
	if (!me->query_temp("lianyao"))
	{
		return notify_fail("你尚未获得云素梅的许可，不要捣乱！\n");
	}
	ob->delete_temp("lianyao");
	ob->delete("lianyao");
	ob->delete_temp("liquid");

	message_vision(WHT"$N弯腰开始清扫药炉，一会将药炉打扫干净！\n"NOR,me);
	return 1;
}
//打开炉盖 1
int do_open(string arg)
{
	    object me = this_player();
        object yc;
		if(!arg)
           return notify_fail("你要打开空气么？\n");
        if (arg!="药炉"&&arg!="lu")
        {
			return notify_fail("你要打开的对象是什么？\n");
        }
		//开盖
        if (this_object()->query("lianyao/open"))
        {
			return notify_fail("炉子已经打开了!\n");
        }
		//煎药中,
        if (this_object()->query("lianyao/fired")||this_object()->query("lianyao/doing"))
        {
			me->receive_wound("qi",(int)me->query("max_qi")/3,"药炉所烫");
			return notify_fail("炉子正在炼药中，你被严重烫伤！\n");
        }

		if (me->is_busy()||me->is_fighting())
		{
		
			return notify_fail("你正在手忙脚乱中，无暇开盖？\n");
       
		}
	
        message_vision(HIY+"\n$N"+HIY+"将药炉的盖轻轻打开。\n"NOR,me);
		
		//me->set_temp("lianyao/open",1);
		this_object()->set("lianyao/open",1);
		//this_object()->set("lianyao/doing", 1);  

		me->add_busy(1);
        return 1;       

}
//放药草 2
int do_fang(string arg)
{
        object me = this_player();
        object yc;
		if(!arg)
                return notify_fail("你要放什么到药炉里去？\n");
        if(!objectp(yc=present(arg, me)))
                return notify_fail("你身上没有"+arg+"这种东西。\n");
        if(!this_object()->query("lianyao/open"))
                return notify_fail("炉盖尚未打开，你不能放"+yc->query("name")+"到药炉里去。\n");
		if(yc->query("id")!="yao cao")
                return notify_fail("你不能放"+yc->query("name")+"到药炉里去。\n");
        if(query("yaocai")>=9)
                return notify_fail("药炉最多放九株药草，现在已经被药材塞满了。\n");
        
		if (this_object()->query("lianyao/fired")||this_object()->query("lianyao/doing"))
        {
			me->receive_wound("qi",(int)me->query("max_qi")/3,"药炉所烫");
			return notify_fail("炉子正在炼药中，你被严重烫伤！\n");
        }

		message_vision(HIY+"\n$N"+HIY+"把一株"+yc->query("name")+HIY"放进药炉。\n"NOR,me);
        yc->move(this_object());
        yc->set("stime",uptime());
        //放置药草标记
		add("yaocai",1);
        //set("zhuyao",1);
		
        return 1;       
}
//加水 3
int do_pour(string arg)
{
        string hehe, what;
        object me, ob, obj;
        me = this_object();
        ob = this_player();
        
		if( !arg
        ||  sscanf(arg, "%s to %s", hehe, what) != 2)
                return notify_fail("请用<pour 容器 to lu>来把水放进炼药炉。\n");

        if( ob->is_busy() ) 
                return notify_fail("你正忙着呢。\n");

        if( ob->is_fighting() )
                return notify_fail("你正在战斗中！\n");

        if( !me->query("lianyao/open") )
                return notify_fail("丹炉的盖子没有打开。\n");

        if( !objectp( obj = present(hehe, ob)))   // 如果你身上的物品的ID不对，不能往丹炉里加水。
                return notify_fail("你身上没有"+hehe+"，如何往炼药炉里加水？\n");
                
        if( !obj->query("liquid/type"))           // 如果你身上的物品不是盛水的器皿，不能往丹炉里加水。
                return notify_fail(obj->name()+"不是盛水的器皿！\n");

        if( !obj->query("liquid/remaining") )     // 判断你身上盛水的器皿中是否还有水。
                return notify_fail(obj->name() + "里面已经一滴不剩了。\n");
        
		if (this_object()->query("lianyao/fired")||this_object()->query("lianyao/doing"))
        {
			me->receive_wound("qi",(int)me->query("max_qi")/3,"药炉所烫");
			return notify_fail("炉子正在炼药中，你被严重烫伤！\n");
        }

        message_vision("$N将一些"+ obj->query("liquid/name") +"从"+ obj->name() +"倒进炼药炉。\n", ob);
        obj->add("liquid/remaining", -1);
        //炉子标记
		me->add_temp("liquid/remaining", 1);
        me->set_temp("liquid/name", obj->query("liquid/name"));
        return 1;
}
//取药草,药草放错了以便调整
int do_qu(string arg)
{
        object me = this_player();
        object yc,yl;

        if(!arg)
                return notify_fail("你要从药炉里拿什么东西？\n");
      
        yl=this_object();
        if(!objectp(yc=present(arg, yl)))
                return notify_fail("药炉里没有"+arg+"这种东西。\n");
        if(yc->query("id")!="yao cao")
                return notify_fail("你不能从药炉里拿"+yc->query("name")+"。\n");
        if( !yl->query("lianyao/open") )
                return notify_fail("丹炉的盖子没有打开，无法取东西。\n");
		if (this_object()->query("lianyao/fired")||this_object()->query("lianyao/doing"))
        {
			me->receive_wound("qi",(int)me->query("max_qi")/3,"药炉所烫");
			return notify_fail("炉子正在炼药中，你被严重烫伤！\n");
        }

		message_vision(HIY+"\n$N"+HIY+"从药炉里拿出了一株药草。\n"NOR,me);
        
		yc->add("times",uptime()-yc->query("stime"));
        yc->move(me);
        add("yaocai",-1);
        if(query("yaocai")<=0)
                set("zhuyao",0);        
        

		return 1;       
}
//盖盖
int do_close(string arg)
{
        object me, ob;
        me = this_object();
        ob = this_player();
        
        if( ob->is_busy() ) 
                return notify_fail("你正忙着呢。\n");

        if( ob->is_fighting() )
                return notify_fail("你正在战斗中。\n");

        if( !arg || arg == "" || arg != "lu")
                return notify_fail("你要关什么？\n");

        if( !me->query("lianyao/open") )      // 判断此时丹炉的盖子是打开还是关上的
                return notify_fail("丹炉的盖子已经盖上。\n");

		if( arg == "lu" )
        {
          message_vision(HIC"$N轻手轻脚的将丹炉的盖子盖上。\n"NOR, ob);
          me->delete("lianyao/open");           // 如果有人把丹炉的盖子关上，那么去掉此标记。
		  
          return 1;
        }

}
//点火
int do_fire(string arg)
{
        object obj;
        object me = this_object();
        object ob = this_player();
        object *inv;
        inv = deep_inventory(me);

        if( ob->is_busy() ) 
                return notify_fail("你正忙着呢。\n");

        if( ob->is_fighting() )
                return notify_fail("你正在战斗中。\n");

        if( me->query_temp("lianyao/open") )
                return notify_fail("丹炉的盖子没有盖上。\n");
        
        if( !objectp( obj = present("fire", ob)))   // 判断玩家身上是否有火折。
                return notify_fail("你需要一个火折。\n");
                
        if( (int)ob->query("neili")  <= 1000 )
                return notify_fail("你的内力不够，点着了火也拉不动风箱。\n");           
                
        if( (int)ob->query("max_neili")  <= 1500 )
                return notify_fail("你的内力不够，点着了火也拉不动风箱。\n");                           

        if( me->query_temp("lianyao/fired"))
                return notify_fail("柴火已经点起来了。\n");   
                
        if(!me->query_temp("liquid/name") ||me->query_temp("liquid/name")!="清水")
                return notify_fail("丹炉里没有水，药草会被熬糊。\n");  
                
        if( !sizeof(inv)) 
                return notify_fail("丹炉里面什么都没有。\n");
                
        message_vision(HIR"\n$N点燃药炉下面的柴火，火苗渐渐地大了起来。\n"NOR, ob);
        //destruct(obj);
		//点火 && 熬药过程
        me->set("lianyao/fired", 1);
       // me->set("lianyao/doing", 1);
        ob->set_temp("lianyao/doing", 1);//正在熬药
        ob->add_busy(1);
//检查药炉状况
		//remove_call_out("do_check");
    //    call_out("do_check", 300);//没有参数ob,药成功不成功和玩家无关
        return 1;
}
//炼药过程
int do_lianyao()
{
	object ob,me;
	int num;
	me=this_player();
	ob=this_object();
	if (!me) return 0;
	num=(int)ob->query("lianyao/marks",1);

	if (me->query("neili")<2500)
	{
		return notify_fail("你的内力不足2500,无法炼药。\n");
	}
	if (me->query("jingli")<2500)
	{
		return notify_fail("你的精力不足2500,无法炼药。\n");
	}
	message_vision(GRN"\n$N运气内功鼓荡，将炉火吹旺，凝神关注，开始炼制药物！\n"NOR,me);
	
	if (!ob->query("lianyao/fired"))
	{
		return notify_fail("你没有点火，如何制药？\n");
	}
	if (!ob->query("yaocai"))
	{
		return notify_fail("药炉内没有药草，如何制药？\n");
	}
	if (random(num)<2+random(3))
	{
		if (!ob->query_temp("liquid/remaining")||ob->query_temp("liquid/name")!="清水")
		{
			
			return do_fail();
		}
		
		switch (random(8))
		{
			case 0:
				tell_object(me,YEL"\n炉火逐渐增大，炉温不断升高，药香弥漫！\n"NOR);
				ob->add("lianyao/marks",1);
				break;
			case 1:
				tell_object(me,MAG"\n一缕药香寻着药炉缝隙透了出来，令人心旷神怡！\n"NOR);
				ob->add("lianyao/marks",1);
				break;
			case 2:
				tell_object(me,BLU"\n忽然有一股火苗过猛，稍许焦糊味道传来！\n"NOR);
				tell_object(me,HIY"心中大急，急忙运用内功控制火苗的势头！\n"NOR);

				ob->add("lianyao/marks",-1);
			
				break;
			case 3:
				tell_object(me,HIM"\n药香缕缕，如烟如雾，令人头脑清醒不少！\n"NOR);
				ob->add("lianyao/marks",2);
				break;
			case 4:
				tell_object(me,HIB"\n药炉中的药似乎传来些许的腥臭气息，似乎有些变味！\n"NOR);
				ob->add("lianyao/marks",-2);
				break;
			case 5:
				tell_object(me,WHT"\n火苗幽幽，药炉中的药物正在缓缓融合，似乎有凝聚的趋势！\n"NOR);
				ob->add("lianyao/marks",1);
				me->improve_skill("zhiyao",(int)me->query_int(1)/2);
				break;
			default:
				tell_object(me,HIW"\n火苗幽幽，半点也不能分心！\n"NOR);
				ob->add("lianyao/marks",1);
				break;
		}
		//remove_call_out("do_lianyao");
		
		call_out("do_lianyao",2);
		
		me->improve_skill("zhiyao",(int)me->query_int(1)/2);
		
		//调用心魔程序
		if (!ob->query_temp("lianyao/xinmo"))
		{
			message_vision(HIR"$N正在凝神炼药，各种药物混合成一股奇怪的药味吸入鼻息，不由地一阵心神恍惚!\n"NOR,me);
			ob->set_temp("lianyao/xinmo",1);
			if (me->query_skill("poison",1)<200)
				me->improve_skill("poison",(int)me->query_int(1)/2);

			call_out("qiangjie",6+random(5),me,1+random(3));
		}
		return 1;
	}
    else{
		//调用灭火程序
		tell_object(me,HIR"\n\n\n药炉中一阵晃动，药香忽然间弥漫整个屋内，药熬好了，赶紧灭火吧！\n"NOR);
		ob->set_temp("lianyao/lianyaodone",1);
		ob->set_temp("lianyao/time",time());
		me->add_busy(2);
		return 1;
	}
	
}
//失败标记
int do_fail()
{
	object me,ob;
	object* inv;
	int i;
	ob=this_object();
	me=this_player();
	inv = deep_inventory(me);

	for (i=0;i>sizeof(inv);i++ )
	{
		destruct(inv[i]);
	}
	me->delete_temp("lianyao");
	ob->delete_temp("lianyao");
	ob->delete_temp("liquid");
	ob->delete("lianyao");

	tell_object(me,WHT"炼药失败，药炉内一片焦糊，刺鼻的味道传来,腥臭难闻!\n"NOR);
	me->apply_condition("flower_poison",2+random(3));
	return 1;
}
//看药
int do_kanyao(string arg)
{
        object me=this_player();
        object yl=this_object();
        object* obs;
        object yc;
        int se,i,j;
        string msg,pre;
        string * day=({ "一","二","三","四","五","六","七","八","九"});
        string * sc=({ "一","二","三","四","五","六","七","八","九","十","十一"});

        if(arg)
        {
                if(!objectp(yc=present(arg, yl)))
                        return notify_fail("药炉里没有"+arg+"这种东西。\n");
                if(!yc->query_temp("lianyao/bad"))
                {
                        se=yc->query("times")+uptime()-yc->query("stime");
                        if(se<=MAXS)
                        {
                                i=se/240;
                                se=se-i*240;
                                pre="("+yc->query("8type")+yc->query("5type")+"性)";
                                msg="已经被煎了";
                                if(i>0)
                                        msg=msg+day[i-1]+"天";
                                i=se/20;
                                if(i>0)
                                        msg=msg+sc[i-1]+"个时辰。\n";
                                else if(msg=="已经被煎了")
                                        msg=msg+"一个时辰不到。\n";
                                msg=pre+msg;
                        }
                        else
                        {
                                msg="。\n";
                                yc->set("name","煎坏了的"+yc->query("name"));
                                yc->set_temp("lianyao/bad",1);
                                tell_object(me,yc->name(1)+msg);
                                destruct(yc);
                                add("yaocai",-1);
								return 1;
                        }
                }
                else
                        msg="。\n";
                tell_object(me,yc->name(1)+msg);
                return 1;
        }       
        obs=all_inventory(yl);
        for(j=0;j<sizeof(obs);j++)
        {
                yc=obs[j];
                if(!yc->query("lianyao/bad"))
                {
                        se=yc->query("times")+uptime()-yc->query("stime");
                        if(se<=MAXS)
                        {
                                i=se/240;
                                se=se-i*240;
                                pre="("+yc->query("8type")+yc->query("5type")+"性)";
                                msg="已经被煎了";
                                if(i>0)
                                        msg=msg+day[i-1]+"天";
                                i=se/20;
                                if(i>0)
                                        msg=msg+sc[i-1]+"个时辰。\n";
                                else if(msg=="已经被煎了")
                                        msg=msg+"一个时辰不到。\n";
                                msg=pre+msg;
                        }
                        else
                        {
                                msg="。\n";
                                yc->set("name","煎坏了的"+yc->query("name"));
                                yc->set_temp("lianyao/bad",1);
                                tell_object(me,yc->name(1)+msg);
                                destruct(yc);
                                add("yaocai",-1);
                                continue;
                        }
                }
				else
                        msg="。\n";
                tell_object(me,yc->name(1)+msg);
        }
        return 1;
}
//熄火
//只有提示成功的条件下灭火才有效。。

int do_miehuo(string arg)
{
        object me, ob;
        object *inv;
		int i;
        me = this_object();
        ob = this_player();
        inv = deep_inventory(me);
		
        if (!arg||arg!="lu")
        {
			return notify_fail("你要给什么灭火？\n");
        }
		if( ob->is_busy())
                return notify_fail("你正忙着呢。\n");
        if( ob->is_fighting())
                return notify_fail("你正在战斗。\n");
        if( !sizeof(inv))
                return notify_fail("炉子里面没有东西。\n");
        if( me->query_temp("lianyao/open") )
                return notify_fail("炉子正开着呢，瞎灭什么火？\n");
        if( !me->query("lianyao/doing") && !me->query("lianyao/fired") )
                return notify_fail("炉子还没点火！\n");
        if( !me->query_temp("lianyao/lianyaodone") )
                return notify_fail("你正在熬药中，还没熬完药呢！\n");

		if (time()-me->query_temp("lianyao/time")>15)
		{
			me->delete_temp("lianyao");
			ob->delete_temp("lianyao");
			ob->delete_temp("liquid");
			ob->delete("lianyao");
			me->delete("lianyao");
			for (i=0;i>=sizeof(inv);i++ )
			{
				destruct(inv[i]);
			}
			return notify_fail("你灭火太迟了，药炉内的药都熬糊了！\n");
		}
		if (present("xinmo",environment(this_object())))
		{
			return notify_fail("你心魔尚未清除，稀里糊涂如何灭火？\n");
		}
		//remove_call_out("do_drug");
        //remove_call_out("do_check");
        //remove_call_out("do_ready");
        //remove_call_out("do_confirm");
        //remove_call_out("do_failed");
        
		//call_out("do_drug", 3 , me);
		message_vision(RED"\n$N把药炉下的柴火渐渐地熄灭了，等待药炉冷却下来。\n"NOR, ob);
		//me->delete("lianyao");
       // ob->delete("lianyao");
		me->set_temp("lianyao/miehuo",1);
		ob->set_temp("lianyao/miehuo",1);
		//me->delete("lianyao/fired");
		me->delete_temp("liquid");
		me->delete("lianyao");
        ob->add_busy(3);
        return 1;

}

//取药
int do_quyao(string arg)
{
        object me=this_player(),yl=this_object(),* obs,yao;
        mapping ycl=(["火":0,"土":0,"金":0,"水":0,"木":0]);
        //mapping 8type=(["乾":0,"坤":0,"震":0,"巽":0,"坎":0,"离":0,"艮":0,"兑":0]);
        mapping yc=([]);
        string type5,type88,* order;
        string* num=({"0","1","2","3","4","5","6","7","8"});
        string* type=({"火","土","金","水","木"});
        string* type8=({"乾","坤","震","巽","坎","离","艮","兑"});
        int i,se,j,sl,sllv,polv,sesx,add,total,k;
        string msg;
        mapping myfam;

        myfam = (mapping)me->query("family");
        if(!myfam || myfam["family_name"] != "神龙教")
        {
           return notify_fail("你不是神龙教弟子，取不了!\n");
        }
        sllv=me->query_skill("shenlong-yaoli",1);
        polv=me->query_skill("poison",1);
        sesx=(sllv+polv/2)*72/10;
        if(sllv<101 || polv<101)
                return notify_fail("你对神龙药理学和毒技的了解还不够，不能制药。\n");
        
		if(!yl->query_temp("lianyao"))
                return notify_fail("药炉里焦糊一片，只剩下一堆黑色药粉！\n");
        //心魔尚在
		//if(me->query_temp("lianyao/rumo"))
          //      return notify_fail("你先克服了心魔再说。\n");

		if (!yl->query_temp("lianyao/miehuo"))
        {
			return notify_fail("火尚未灭，你不怕烫手？\n");
        }
		if (!yl->query("lianyao/open"))
        {
			return notify_fail("药炉尚未打开，你如何取药？\n");
        }

		obs=all_inventory(yl);
        
		if(sizeof(obs)==0)
                return notify_fail("药炉里没有东西。\n");
        msg=me->query("id");
        for(i=0;i<sizeof(obs);i++)
{
                if(obs[i]->query("id")!="yao cao")
                        continue;
                se=obs[i]->query("times")+uptime()-obs[i]->query("stime");
                if(se>MAXS)
                {
                        obs[i]->set("name","煎坏了的"+obs[i]->query("name"));
                        obs[i]->set("lianyao/bad",1);
                        destruct(obs[i]);
                        add("yaocai",-1);
                        continue;
                }
                if(se>sesx)
                        se=sesx;
                type5=obs[i]->query("5type");
                type88=obs[i]->query("8type");
                msg=sprintf("%s %s%s:%d",msg,type5,type88,se);
                if(sizeof(yc)==0)
                {
                        yc=([ type5:([type88:([num[i]:se])])]);
                }
                else
                {
                        if( undefinedp(yc[type5]) )
                        {
                                yc[type5]=([type88:([num[i]:se])]);
                        }
                        else if( undefinedp(yc[type5][type88]))
                        {
                                yc[type5][type88]=([num[i]:se]);
                        }
                        else
                        {
                                yc[type5][type88][num[i]]=se;
                        }       
                }
                destruct(obs[i]);
                add("yaocai",-1);
        }
        add=0;
		for(i=0;i<5;i++)
        {
                if( undefinedp(yc[type[i]]))
                        continue;
                else if(sizeof(yc[type[i]])>=8)
                {
                        sl=10000;
                        for(j=0;j<8;j++)
                        {
                                if( undefinedp(yc[type[i]][type8[j]]))
                                        continue;
                                order=keys(yc[type[i]][type8[j]]);
                                if(yc[type[i]][type8[j]][order[0]]<sl)
                                        sl=yc[type[i]][type8[j]][order[0]];
                                map_delete(yc[type[i]][type8[j]],order[0]);
                                if(sizeof(yc[type[i]][type8[j]])==0)
                                        map_delete(yc[type[i]],type8[j]);
                        }
                        ycl[type[i]]=sl*64;
                }
                else
                {
                        for(k=0;k<2;k++)
                        {
                                while(1)
                                {
                                        for(j=k;j<8;j++,j++)
                                        {
                                                if(undefinedp(yc[type[i]][type8[j]]))
                                                        break;
                                        }
                                        if(j>=8)
                                        {
                                                sl=10000;
                                                for(j=k;j<8;j++,j++)
                                                {
                                                        if( undefinedp(yc[type[i]][type8[j]]))
                                                                continue;
														order=keys(yc[type[i]][type8[j]]);
                                                        if(yc[type[i]][type8[j]][order[0]]<sl)
                                                                sl=yc[type[i]][type8[j]][order[0]];
                                                        map_delete(yc[type[i]][type8[j]],order[0]);
                                                        if(sizeof(yc[type[i]][type8[j]])==0)
                                                                map_delete(yc[type[i]],type8[j]);
                                                }
                                                ycl[type[i]]=ycl[type[i]]+sl*16;
                                        }
                                        else
                                                break;
                                }
                        }
                        for(k=0;k<4;k++)
                        {
                                while(1)
                                {
                                        for(j=k*2;j<k*2+2;j++)
                                        {
                                                if(undefinedp(yc[type[i]][type8[j]]))
                                                        break;
                                        }
                                        if(j>=k*2+2)
                                        {
                                                sl=10000;
                                                for(j=k*2;j<k*2+2;j++)
                                                {
                                                        if( undefinedp(yc[type[i]][type8[j]]))
                                                                continue;
                                                        order=keys(yc[type[i]][type8[j]]);
                                                        if(yc[type[i]][type8[j]][order[0]]<sl)
                                                                sl=yc[type[i]][type8[j]][order[0]];
                                                        map_delete(yc[type[i]][type8[j]],order[0]);
                                                        if(sizeof(yc[type[i]][type8[j]])==0)
                                                                map_delete(yc[type[i]],type8[j]);
                                                }
                                                ycl[type[i]]=ycl[type[i]]+sl*4;
                                        }
                                        else
                                                break;
}
                        }
                }
                for(j=0;j<8;j++)
                {
                        if( undefinedp(yc[type[i]][type8[j]]))
                                        continue;
						order=keys(yc[type[i]][type8[j]]);
                        for(k=0;k<sizeof(order);k++)
                        {
                                ycl[type[i]]=ycl[type[i]]+yc[type[i]][type8[j]][order[k]];
                                map_delete(yc[type[i]][type8[j]],order[k]);
                        }
                        map_delete(yc[type[i]],type8[j]);
                }
                add+=ycl[type[i]];
        }
        total=add;
        add/=200;
        if(add>100)
                add=100;
        me->improve_skill("shenlong-yaoli",add,0);
        me->improve_skill("poison",add,0);
       //增加制药术
		me->improve_skill("zhiyao",add,0);

        yao=new("/d/sld/npc/obj/yaowan");
        if(!objectp(yao))
                return notify_fail("可惜，你的药被煎坏了。\n");
        msg=msg+" "+file_name(yao);
        j=0;k=0;
        yao->set("types",0);
        for(i=0;i<5;i++)
        {
                if(ycl[type[i]]<total*1/20)
                        continue;
                yao->add("types",1);
                if(type[i]=="土")
                {
                        yao->set(type[i],ycl[type[i]]/100);
                        msg=sprintf("%s %s:%d",msg,type[i],ycl[type[i]]/100);
                }
                else
{
                        yao->set(type[i],ycl[type[i]]/10);
                        msg=sprintf("%s %s:%d",msg,type[i],ycl[type[i]]/10);
                }
                if(ycl[type[i]]>=total*7/10)
                        k=i+1;
                else if((ycl[type[i]]>=total*19/100) && (ycl[type[i]]<=total*21/100))
                        j++;
        }
        if(k>0)
        {
                yao->set("poison",type[k-1]);
                yao->set("zycs",ycl[type[k-1]]/1000);
                msg=sprintf("%s %s::%d",msg,type[k-1],ycl[type[k-1]]/1000);
        }
        else if(j==5)
        {
                yao->set("poison","全");
                yao->set("zycs",total/1000);
                msg=sprintf("%s 全::%d",msg,total/1000);        
        }
        msg=msg+"。\n";
//	write_file("/u/emnil/makeyao",msg);
        write("你打算给这颗药起个什么英文名字？(缺省：danyao)");
		yao->move(me);
        input_to("yao_id",0,yao);
        return 1;
}

void yao_id(string arg,object yao)
{
        if(arg && arg!="")
                yao->set("id",arg);
        else
                yao->set("id","danyao");
		this_player()->set_temp("lianyao/yaoid",arg);

        write("你打算给这颗药起个什么中文名字？(缺省：丹药)");
        input_to("yao_name",0,yao);
}

void yao_name(string arg,object yao)
{
        yao->set_name(HIG "丹药" NOR, ({yao->query("id"),"yao","dan"}));
		if(arg && arg!="")
        yao->set("name",arg);
		this_player()->set_temp("lianyao/yaoname",arg);

        write("你打算如何描述这颗药？(缺省：这是一颗神龙教独家密制的丹药。)");
        input_to("yao_long",0,yao);
}

void yao_long(string arg,object yao)
{
    int i,add,qnadd;
	object ob;
    object me=this_player();
	ob=this_object();

	if(arg && arg!="")
		yao->set("long",arg+"\n");
        message_vision(HIY+"\n$N"+HIY+"终于从心魔中醒来，从药炉里拿出了一颗药丸子。\n"NOR,me);
        yao->set("owner",me->query("id"));
		this_player()->set_temp("lianyao/yaolong",arg);

		if(!yao->move(me))
                yao->move(environment(me));
		ob->delete_temp("lianyao");
		ob->delete("lianyao");

       /* 
		if((add=me->query("mkyexp"))!=0)
        {
                i=me->query("max_pot")-me->query("potential");
                qnadd=add/2;
                if ( i<qnadd) qnadd = i;
                
                me->add("combat_exp",add);
                me->add("potential",qnadd);
                me->add("shen",-add*2);
                me->delete("mkyexp");

                tell_object(me,"你战胜心魔，获得了"+add+"点经验，"+qnadd+"点潜能，"+add*2+"点负神！\n");
        }*/
}
