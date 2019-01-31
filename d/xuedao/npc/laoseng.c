// laoseng.c 血刀长老老僧
// by sohu@xojh
#include <ansi.h>
inherit NPC;

string ask_bladebook();
string ask_miji();
string ask_gushi();
string ask_lansha();

void create()
{
	set_name("老僧", ({"lao seng","seng"}));
	set("long",
                "他是血刀老祖的师弟，生得身高体阔，虎背熊腰，满脸的横肉，一双绿豆小眼\n"
                "朝四外来回打量着,尽管年纪老迈，但人却极为精壮。\n"
	);

    set("title", "血刀门掌门师弟");
	set("gender", "男性");
	set("attitude", "peaceful");
	set("class", "huanxi");

	set("inquiry",([
		"刀法大全"	: (: ask_bladebook :),
		"血刀秘籍"	: (: ask_miji :),
		 "故事"	: (: ask_gushi :),
		"蓝砂手绝技"	: (: ask_lansha :),

	]));

	set("age", 30);
	set("shen_type", -1);
	set("str", 25);
	set("int", 15);
	set("con", 25);
	set("dex", 20);
	set("max_qi", 22450);
	set("eff_jing", 6200);
	set("max_jing", 6200);
	set("neili", 12500);
	set("max_neili", 12500);
	set("jiali", 200);
	set("combat_exp", 9300000);
	set("score", 1000);
	set("unique", 1);
	set("book1",1);
		set("book2",1);

	set_skill("force", 450);
	set_skill("xuedao-jing", 450);
	set_skill("dodge", 450);
	set_skill("xueying-dunxing", 450);
	set_skill("strike", 450);
	set_skill("hongsha-zhang", 450);
	set_skill("parry", 450);
	set_skill("huanxi-chan", 150);
	set_skill("literate", 230);
	set_skill("blade", 480);
	set_skill("xuedao-daofa", 480);
	set_skill("hand", 480);
	set_skill("lansha-shou", 480);
	set_skill("throwing", 480);

	map_skill("force", "xuedao-jing");
	map_skill("dodge", "xueying-dunxing");
	map_skill("strike", "hongsha-zhang");
	map_skill("parry", "xuedao-daofa");
	map_skill("blade", "xuedao-daofa");
	map_skill("throwing", "lansha-shou");

	prepare_skill("strike", "hongsha-zhang");

	create_family("血刀门", 4, "掌门师叔");
	
	setup();
    carry_object("clone/weapon/blade")->wear();
    carry_object("d/xuedao/obj/qinxiu-jiasha")->wear();
}
//基本刀法book2

string ask_bladebook()
{
	object me,ob;

	me = this_player();

	if (me->query("family/family_name") != "血刀门")
		return RANK_D->query_respect(me) + "不是在开玩笑吧。\n";

	if( me->query("class")!="huanxi" )
		return "你不是我血刀门欢喜禅弟子。\n";
	if( me->query_temp("asklaoseng/blade2"))
		return "你方才不是已经拿过一本了么？。\n";
	if( this_object()->query("book1")<1)
		return "方才有人将这本刀法大全拿走了？。\n";

	if( (string)me->query("gender") == "无性" )
		return "施主身体残缺，虽说佛祖普渡众生，可是我血刀门完全靠那玩意，.……\n";

	if (me->query_skill("blade",1)<60)
		return "你目前的基本刀法水平太低，不足60级，要了那书也没用。\n";
	if (present("daofa daquan",me))
		return RANK_D->query_respect(me) + "你身上不是有一本么？\n";
	if (present("daofa daquan",environment(me)))
		return RANK_D->query_respect(me) + "地上不是有一本么？\n";
	this_object()->add("book1",-1);
	me->set_temp("asklaoseng/blade2",1);
	ob=new("d/xuedao/obj/bladebasic_book");	
	ob->move(me);
	
	return "你如此辛苦修炼，我就把这本门派《刀法大全》给你参阅，千万别给弄丢了。\n";
}
//基本刀法book3

string ask_miji()
{
	object me,ob;

	me = this_player();

	if (me->query("family/family_name") != "血刀门")
		return RANK_D->query_respect(me) + "不是在开玩笑吧。\n";
	if( me->query("class")!="huanxi" )
		return "你不是我血刀门欢喜禅弟子。\n";
	if( me->query_temp("asklaoseng/blade3"))
		return "你方才不是已经拿过一本了么？。\n";
	if( query("book2")<1)
		return "方才有人将这本刀法大全拿走了？。\n";
	if( (string)me->query("gender") == "无性" )
		return "施主身体残缺，虽说佛祖普渡众生，可是我血刀门完全靠那玩意，.……\n";

	if (me->query_skill("blade",1)<120)
		return "你目前的基本刀法水平太低，不足120级，要了那书也没用。\n";
	if (!me->query("quest/xd/dichuan"))
		return "你目前不是嫡传弟子，怎么可能给你这本书。\n";
	if (present("daofa jingyao",me))
		return RANK_D->query_respect(me) + "你身上不是有一本么？\n";
	if (present("daofa jingyao",environment(me)))
		return RANK_D->query_respect(me) + "地上不是有一本么？\n";
	this_object()->add("book2",-1);
	me->set_temp("asklaoseng/blade3",1);

	ob=new("d/xuedao/obj/blade_book");	
	ob->move(me);
	
	return "这本书是我血刀门刀法集大成的刀法独有秘籍《血刀刀法精要》，你可要好好保管。\n";
}

string ask_gushi()
{
	object me,ob;

	me = this_player();

	if (me->query("family/family_name") != "血刀门")
		return RANK_D->query_respect(me) + "不是在开玩笑吧。\n";
	if( me->query("class")!="huanxi" )
		return "你不是我血刀门欢喜禅弟子。\n";
	if (me->query_skill("force",1)<200)
	{
		return "你的基本内功火候不到，告诉你也没用\n";
	}

	if (!me->query_temp("xd/laoseng/start"))
	{
		command("say 如果你真想听我的故事，就要给老僧我多多供奉！\n");
		command("say 我最喜欢吃五露丸子了，哪怕有五肉丸子也行！\n");

		return "要是不孝敬我，就别来聒噪我，没看我在潜修么？！\n";
	}
	command("say 在我年轻的时候，喜欢上邻村的一个姑娘。\n");
	command("say 我们经常一起玩耍，一起游乐，那时是我最开心的日子。\n");
	command("say 后来，她被村里一个恶霸看上了。\n");
	command("say 就设定计谋把我陷害，然后就把我关押在大牢。\n");

	command("say 我出狱后发现我心爱的姑娘已经被那个恶霸霸占了。\n");
	command("say 我的房子也给卖了。\n");

	command("say 我咽不下这口气就把那恶霸的房子给点了。\n");
	command("say 后来我就被毒打一顿，奄奄一息，差点死了。\n");
	command("say 我发誓不报此仇誓不为人，决定招高人学艺，出这口恶气！\n");
	command("say 在崆峒门下学了这蓝砂手。\n");

	command("say 学艺有成后，我一直想去把那个恶霸全家都给杀了。\n");
	command("say 包括那个姑娘，全给杀了。\n");
	command("say 可因为修炼功夫，一直没能如愿。\n");
	command("say 后来我就到血刀门拜师学艺。\n");
	command("say 一直到今天，方的大成。\n");

	me->set_temp("xd/laoseng/ask",1);

	return "这蓝砂手可以当手法也可以发暗器，着实厉害。\n";
}

string ask_lansha()
{
	object me,ob;

	me = this_player();
	if (time()-me->query("quest/xd/lansha/time")<86400)
	{
		//command("say 你");
		return "你来的太频繁了，武功最忌讳心气浮躁？？\n";
	}

	if (!me->query_temp("xd/laoseng/ask"))
	{
		return "我最喜欢吃五露丸子了，哪怕有五肉丸子也行！？\n";
	}
	if (!me->query_temp("xd/laoseng/taskok"))
	{
		command("say 既然你想学这门绝技，那你就去佛山把凤天南那个恶霸给我杀了。\n");
		command("say 帮我出这口恶气先。\n");
		me->set_temp("xd/laoseng/killfeng",1);
		return "你去把凤天南给我杀了，不出这口恶气，我凭什么教你？\n";
	}
	command("say 老僧我着实为你感到高兴，看在你平时时常孝敬我五肉丸子和五露丸子的份上\n我就传授你这蓝砂手绝技！\n");
	call_out("study_lansha",1,me);
	return "这凤天南就是个恶霸。\n";
}

int study_lansha(object me)
{
	
	int i,j; 
	if(!me) return 0;
	i=random(me->query("kar"));
	j=20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
	j=random(j);
	if (me->query("family/family_name")!="血刀门")
	{
		return notify_fail("你不是血刀门弟子，来此消遣我么？\n");
	}

	if (me->query("quest/xd/lansha/pass"))
	{
		
		return notify_fail("你已经解开了这个谜题，你无缘无故来找我作甚？？\n");
	}


	if (time()-me->query("quest/xd/lansha/time")<86400)
	{
		//command("say 你");
		return notify_fail( "你来的太频繁了，武功最忌讳心气浮躁？？\n");
	}
	if (!me->query("quest/xd/dichuan"))
	{
		//command("say 你");
		return notify_fail( "血刀需要的是始终如一的忠诚弟子，你非嫡传，焉能传授你高级武功？？\n");
	}
	if (me->query_skill("force",1)<200)
	{
		//command("say 你");
		return notify_fail("练习基本内功需要到200才能修习蓝砂手，还是好好修炼去吧？？\n");
	}

	if (i>23
	  && j<5
	  && me->query("kar")<31)
 	{ 
        
         me->start_busy(3);
		 message_vision(HIB"\n$N磨了半天，手腕寸关穴忽然一痛，这蓝砂手经络豁然打通。”\n"NOR,me); 
         message_vision(HIY"\n$N心中大喜，「哈哈哈」仰天大笑几声，说道：“原来如此，原来如此。”\n"NOR,me); 
         message_vision(HBYEL+HIW"\n$N经过不断研磨练习领悟，终于领悟了老僧所传授的蓝砂手的奥秘！”\n"NOR,me); 
         log_file("quest/xdlansha", sprintf("%s(%s) 蓝砂手解密成功！第%d次参悟，机缘巧合下，成功参悟蓝砂手技的奥秘，随机幸运值：%d,当前随机值：%d,当前经验：%d,\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/xd/lansha/fail"),
		 i,
		 j,
         me->query("combat_exp"),
		 ));

		 me->set("quest/xd/lansha/time",time());
		 me->set("quest/xd/lansha/pass",1);
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N神情沮丧，自言自语地说道：“看来这蓝砂手真是不好解啊，继续努力吧。”\n"NOR,me); 
		 message_vision(HIY"\n参悟蓝砂手绝技解密失败！\n"NOR,me); 
         log_file("quest/xdlansha", sprintf("%s(%s) 失败！参悟蓝砂手第%d次失败，随机幸运值：%d,当前随机值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/xd/lansha/fail",1),
		 i,
		 j,
         me->query("combat_exp"),));        
		 me->add("quest/xd/lansha/fail",1);
		 me->set("quest/xd/lansha/time",time());
		 me->start_busy(2);
		 me->delete_temp("quest/xd/lansha/modao");
		 me->delete_temp("quest/xd");
		 return 1;
   }
	

}
	
int accept_object(object who,object obj)
{
	object obb;
	int i;
	i=who->query("quest/xd/xiaojing/times");
	
	if ((obj->query("id")=="wulu wan"||obj->query("id")=="wurou wan")
		&&obj->query("owner")==who->query("id"))
	{
		if (random(i)>200
			&&random(who->query("kar"))>20)
		{
			command("say 我观察你好久了，发现你这小伙子不错！\n");
			command("say 数年以来一直给老衲我供奉各种丸子！\n");
			command("say 老衲我今天很高兴，就给你讲讲我的故事，如何？！\n");
			who->set_temp("xd/laoseng/start",1);
		}
		command("say 能得到你的孝敬，老僧我很开心.\n");
		who->add("quest/xd/xiaojing/times",1);
		destruct(obj);
		return 1;

	}
	
	else if (who->query_temp("xd/laoseng/killfeng")
		&&objectp(obb=obj->query("kill_by"))
		&&obj->query("name")=="凤天南的首级"
		&&obb->query("id")==who->query("id"))
	{
		command("haha "+who->query("id"));
		command("say 你能将"+obj->query("victim_name")+"这个恶霸给我杀了，我很高兴！\n");
		command("pat "+who->query("id"));
		command("say 这说明你最近武功修炼不错，我很看好你！\n");
		destruct(obj);
		who->set_temp("xd/laoseng/taskok",1);
		return 1;
	}	
	command("say 你心不诚实啊，这肉丸子虽然滋味不错，但缺的是你亲自替老僧炼制的效果啊！\n");
	return 0;
	
}

