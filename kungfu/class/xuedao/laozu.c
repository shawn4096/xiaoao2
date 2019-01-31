// laozu.c 血刀老祖
// by iceland

#include <ansi.h>
#include "/d/suzhou/npc/lchj.h";
#include "laozu.h";
#include <job_mul.h>
#include <get_place.h>

inherit NPC;
inherit F_MASTER;

string ask_yaoshi();
string ask_pizhi();
string ask_zujixiake();
string ask_xgjz();
string ask_fail();
string ask_hxjue();
string ask_jingang();

string ask_xuedao();
string ask_zijindao();
string ask_diyun();
string ask_xuedaojj();
string ask_xuesha();

string *names = ({
"/d/xuedao/shandong1","/d/xuedao/shandong2","/d/xuedao/shandong3","/d/xuedao/hollow","/d/xuedao/huangxidong1",
"/d/xuedao/shandong31","/d/xuedao/shandong32","/d/xuedao/chucangshi","/d/xuedao/huangxidong2","/d/xuedao/huangxidong3",
"/d/xuedao/sroad9","/d/xuedao/wangyougu","/d/xuedao/shulin2","/d/xuedao/huangxidong4","/d/xuedao/kengdao1","/d/xuedao/kedao2",
"/d/xuedao/shulin1","/d/xuedao/shulin3","/d/xuedao/shulin4","/d/xuedao/kedao3","/d/xuedao/kedao4",
"/d/xuedao/sroad8","/d/xuedao/sraod7","/d/xuedao/sroad6","/d/xuedao/sroad5","/d/xuedao/lingwushi",
"/d/xuedao/sroad4","/d/xuedao/sraod3","/d/xuedao/sroad2","/d/xuedao/sroad1","/d/xuedao/midong",
"/d/xuedao/sroad9","/d/xuedao/nroad1","/d/xuedao/nroad2","/d/xuedao/nroad3","/d/xuedao/shitang",
"/d/xuedao/nroad4","/d/xuedao/nroad5","/d/xuedao/nroad6","/d/xuedao/nroad7","/d/xuedao/shufang"
});


void create()
{
	object weapon;
	set_name("血刀老祖", ({ "xuedao laozu", "laozu","xuedaolaozu" }));
	set("long",@LONG
他身材高瘦，眼窝深陷，一双眼睛射出凶狠的光芒，令人不敢直视。他在江湖
中以残忍好色而著称，曾凭一手血刀经的功夫斗败无数中原的武林豪杰。
LONG
	);
	set("title", HIR "血刀门掌门" NOR);
	set("gender", "男性");
	set("class", "huanxi");
	set("age", 65);
	set("attitude", "friendly");
	set("shen_type", -1);
	set("str", 35);
	set("int", 30);
	set("con", 35);
	set("dex", 35);
	set("max_qi", 32100);
	set("eff_jing", 9600);
	set("max_jing",9600);
	set("max_jingli",8600);
	set("eff_jingli", 8600);
	set("no_bark",1);
	set("book",1);

	set("neili", 32500);
	set("max_neili", 32500);
	set("jiali", 250);
	set("combat_exp", 12500000);
	set("score", 500000);
	set("unique", 1);
	set("quest/xd/xddf/huaxue/pass",1);
	set("quest/xd/xddf/pizhi/pass",1);
	set("quest/xd/xdj/xuedao/pass",1);
	set("quest/xd/jglts/jingang/pass",1);
	set("quest/xd/xddf/chilian/pass",1);

	set_skill("huanxi-chan", 200);
	set_skill("literate", 250);
	set_skill("force", 500);
	set_skill("xuedao-daofa", 520);
	set_skill("dodge", 500);
	set_skill("xueying-dunxing", 500);
	set_skill("strike", 500);
	set_skill("hongsha-zhang", 500);
	set_skill("hand", 500);
	set_skill("lansha-shou", 500);
	set_skill("blade",520);
	set_skill("xuedao-jing",500);
	set_skill("parry", 500 );
	set_skill("jingang-liantishu", 500 );

	map_skill("force", "xuedao-jing");
	map_skill("dodge", "xueying-dunxing");
	map_skill("hand", "lansha-shou");
	map_skill("parry", "jingang-liantishu");
	map_skill("strike", "hongsha-zhang");
	map_skill("blade", "xuedao-daofa");

	prepare_skill("hand","lansha-shou");
	prepare_skill("strike","hongsha-zhang");

	create_family("血刀门", 4, "掌门");
	set("class", "huanxi");
	set("inquiry", ([
		"要事" : (: ask_yaoshi :),
		"血刀" : (: ask_xuedao :),
		"紫金刀" : (: ask_zijindao :),

		"阻击侠客" : (: ask_zujixiake :),
		"雪谷激战" : (: ask_xgjz :),
		"任务失败" : (: ask_fail :),
		"血刀经秘笈" : (: ask_xuedaojj :),
		"血煞" : (: ask_xuesha :),

		"化血诀绝技" : (: ask_hxjue :),
		"金刚炼体术绝技" : (: ask_jingang :),
		"狄云" : (: ask_diyun :),

	]));

	set("chat_chance", 2);
	set("chat_msg", ({
		"血刀老祖抬起头，若有所思的自言自语：“月亮快圆了，得下山杀个人祭祭刀了。”\n",
		"血刀老祖恨恨的说：“什么时候再入中原，再闹个天翻地覆！”\n",
		"血刀老祖咬牙切齿，眼露凶光的说：“下次来个斩草除根，一个活口也不留！”\n",
		"血刀老祖自言自语道：“年纪大了，体力可一点也不含糊。”言下甚为得意。\n",
	}) );
	set("chat_chance_combat", 100);
	set("chat_msg_combat", ({
		(: exert_function, "yuxue" :),
		(: exert_function, "xuedao" :),
		(: exert_function, "xuesha" :),
		(: perform_action, "blade.chuanxin" :),
		(: perform_action, "blade.liuxing" :),
		(: perform_action, "blade.shendao" :),
		(: perform_action, "blade.chilian" :),
		(: perform_action, "blade.bafang" :),
		(: perform_action, "blade.huaxue" :),
		(: perform_action, "blade.pizhi" :),
		(: perform_action, "blade.jixue" :),

	}));

	setup();
	carry_object("/d/xueshan/npc/obj/longxiang-jiasha")->wear();
	if (clonep()){
		weapon = unew("clone/weapon/blade/xuedao");
		if(!weapon)weapon=new(BINGQI_D("xinyuedao"));
		weapon->move(this_object());
		weapon->wield();
	}
	//add_money("gold",5);
}
//收徒
void attempt_apprentice(object ob)
{
        if ((string)ob->query("family/family_name") != "血刀门") {
               command("say"+ RANK_D->query_respect(ob) +
                        "不是本门弟子，在这里捣什么乱？！");
                return;
        }

        if ((int)ob->query_skill("huanxi-chan", 1) < 200) {
                command("say 欢喜禅是各项武功之本，不够200，你再勤加修炼吧。");
                command("say"+ RANK_D->query_respect(ob) +
                        "再熬几个通宵，多多钻研钻研本门的心法吧。");
                return;
        }
        if ((int)ob->query_skill("jingang-liantishu", 1) < 350) {
                command("say 金刚炼体术是各项武功之本，不足350，你再勤加修炼吧。");
                command("say"+ RANK_D->query_respect(ob) +
                        "再熬几个通宵，多多练习吧。");
                return;
        }

        if ((int)ob->query_skill("xuedao-jing", 1) < 350) {
                command("say 血刀经是各项武功之本，不足350，你再勤加修炼吧。");
                command("say"+ RANK_D->query_respect(ob) +
                        "再熬几个通宵，多多练习吧。");
                return;
        }
        if (!ob->query("quest/xd/dichuan")) {
                command("say 你没有嫡传身份，我不敢收你。");
                return;
        }
        if (ob->query("job_time/血刀阻击")<2000) {
                command("say 你做的血刀阻击任务尚不足2000次，我不愿意收你。");
                return;
        }
		if ((int)ob->query("shen") > -2000000) {
			command("hmm");
			command("say 我血刀老祖声名远扬，那些所谓的江湖大侠哪个不是望风而逃？");
			command("say 以你现在的资历，如果收你为徒，恐怕会被人耻笑。");
			return;
		}

        command("say 好吧，以后你就好好侍奉佛爷我吧。");
        command("chat 从今以后，"+ob->query("name")+"就是佛爷我的亲传弟子，谁要是敢欺负我的乖徒儿，可别怪佛爷我心狠手辣！\n");
		command("chat 不服气的就问问我手中的血刀吧!\n");
        command("recruit " + ob->query("id"));
        ob->set("title", HIR "血刀老祖亲传弟子" NOR);
		return ;

}
//启动血刀刀法批纸削腐的quest
string ask_yaoshi()
{
	object me;
	me=this_player();

	if (me->query("family/family_name")!="血刀门")
	{
		return "你不是血刀门弟子，来此消遣老祖我么？\n";
	}
	if (me->query("quest/xd/xddf/pizhi/pass"))
	{
		me->set("title",HBRED"血刀刀法传人"NOR);
		return "你已经解开了这个谜题，你无缘无故来找我作甚？？\n";
	}
//启动来自捉美女任务
	if (!me->query_temp("quest/xd/xddf/pizhi/start"))
	{
		return "你平时也不孝敬孝敬老祖我，现在无缘无故来找我作甚？？\n";
	}
	if (time()-me->query("quest/xd/xddf/pizhi/time")<86400)
	{
		//command("say 你");
		return "你来的太频繁了，武功最忌讳心气浮躁？？\n";
	}
	if (!me->query("quest/xd/dichuan"))
	{
		//command("say 你");
		return "我大血刀需要的是始终如一的忠诚弟子，你非我嫡传，焉能传授你高级武功？？\n";
	}
	if (me->query("int")<40)
	{
		//command("say 你");
		return "练习血刀刀法需要的是高悟性，你先天不足40，还是好好修炼去吧？？\n";
	}
	command("say 我听你宝象师兄说最近你替老祖我抢了不少美女");
	command("say 我才知晓最近几个小妞都是你小子孝敬老祖我的，老祖心怀甚慰！\n");
	command("say 既然你如此有孝心，老祖我就指点指点你！\n");
	command("say 老祖我当初在一练功室中曾留下一个练功场所！\n");
	command("say 那个地方有两处练刀法好地方！\n");
	command("say 一处练习批纸技的所在，一处是练习削腐技的所在！\n");
	command("say 批纸技是你要练习刀法在一堆纸中一刀下去，只劈出一张纸方为成功！\n");
	command("say 削腐技是你要练习刀法在一块豆腐中一刀下去，只劈出像纸片一样厚的豆腐片方为成功！\n");
	command("say 这两大技能是我血刀门练习血刀刀法的不二法门！\n");
	command("say 你好好练习，练成后再来见我！\n");
	command("heng ");
	me->delete_temp("quest/xd/xddf/pizhi/start");
	me->set("quest/xd/xddf/pizhi/asklaozu",1);
	return "一刀在手，天下我有！\n";
}
//金刚炼体术，然后去雪谷中炼体
string ask_jingang()
{
	object me;
	me=this_player();

	if (me->query("family/family_name")!="血刀门")
	{
		return "你不是血刀门弟子，来此消遣老祖我么？\n";
	}
	if (me->query("quest/xd/jglts/jingang/pass"))
	{
		//me->set("title",HBRED"血刀刀法传人"NOR);
		return "你已经解开了这个谜题，你无缘无故来找我作甚？？\n";
	}

	if (time()-me->query("quest/xd/jglts/jingang/time")<86400)
	{
		//command("say 你");
		return "你来的太频繁了，武功最忌讳心气浮躁？？\n";
	}
	if (!me->query("quest/xd/dichuan"))
	{
		//command("say 你");
		return "我大血刀需要的是始终如一的忠诚弟子，你非我嫡传，焉能传授你高级武功？？\n";
	}
	if (me->query_skill("xuedao-jing",1)<350)
	{
		//command("say 你");
		return "练习血刀经不足350，还是好好修炼去吧？？\n";
	}
	command("say 这金刚炼体术是我门下不传之秘，你要从小认真完成老祖我交代给你的任务才行。");
	command("say 让我先检查下你的功劳簿！\n");
	command("say 到目前为止你已经完成了：\n");
	
	command("say 采血采肉需要200次，你已经完成了："+me->query("job_time/血刀打猎")+"\n");
	
	if (me->query("job_time/血刀打猎")>200)
	{
		command("say 采肉打猎任务通过！\n");

	} else return "继续努力去完成血刀打猎job,直到200次为止。\n";
	
	command("say 刀警戒任务需求800次，你总计完成："+me->query("job_time/血刀警戒")+"次\n");
	if (me->query("job_time/血刀警戒")>800)
	{
		command("say 血刀警戒任务通过！\n");

	}else {
		return "继续努力去完成血刀警戒job,直到800次为止。\n";
		
	}

	
	command("say 阻击侠客任务需要2000次，总计完成："+me->query("job_time/血刀阻击")+"次\n");
	if (me->query("job_time/血刀阻击")>2000)
	{
		command("say 血刀阻击任务通过！\n");

	} else return "继续努力去完成血刀阻击侠客job,直到2000次为止。\n";
		
	command("say 你千万要记住了，这些辛苦老祖我都看在眼里，这也是老祖考验你的一种方式。\n");
	command("say 老祖我非常开心，真是我大血刀不错的弟子。\n");
	command("say 既然你如此努力修炼，如此忠诚于我血刀门，我就告诉你这个秘密！\n");
	command("say 此门武功必须要到大雪山的深谷中去修炼！\n");
	command("say 因雪谷中雪层较厚，你须得深吸一口真气，然后将自己头朝下埋入雪中，！\n");
	command("say 再辅助以我血刀门独特运气心法来运使真气行使各经脉！\n");
	command("say 修炼法门独特，但功力增长奇快，这也是我大血刀的独到之处！\n");
	command("say 你若修成此门神功，就会打下非常好的底子！\n");
	command("say 未来不可限量！\n");
	command("consider ");
	command("say 什么江南四侠等人物不过是跳梁小丑而已！\n");

	me->set_temp("quest/xd/jglts/jingang/start",1);

	return "金刚炼体就是练就金刚体的意思！\n";
}
//化血诀绝技，然后去山洞密洞磨刀

string ask_hxjue()
{
	object me;
	me=this_player();

	if (me->query("family/family_name")!="血刀门")
	{
		return "你不是血刀门弟子，来此消遣老祖我么？\n";
	}
	if (me->query("quest/xd/xddf/huaxue/pass"))
	{
		//me->set("title",HBRED"血刀刀法传人"NOR);
		return "你已经解开了这个谜题，你无缘无故来找我作甚？？\n";
	}

	if (time()-me->query("quest/xd/xddf/huaxue/time")<86400)
	{
		//command("say 你");
		return "你来的太频繁了，武功最忌讳心气浮躁？？\n";
	}
	if (!me->query("quest/xd/dichuan"))
	{
		//command("say 你");
		return "我大血刀需要的是始终如一的忠诚弟子，你非我嫡传，焉能传授你高级武功？？\n";
	}
	if (me->query_skill("xuedao-daofa",1)<300)
	{
		//command("say 你");
		return "练习血刀刀法不足300，还是好好修炼去吧？？\n";
	}
	command("say 这化血诀是我门下不传之秘，你要从小认真完成老祖我交代给你的任务才行。");
	command("say 让我先检查下你的功劳簿！\n");
	command("say 到目前为止你已经完成了：\n");


	command("say 采血采肉打猎任务总计"+me->query("job_time/血刀打猎")+"次\n");
	command("say 采血刀警戒任务总计"+me->query("job_time/血刀警戒")+"次\n");
	command("say 你千万要记住了，这些辛苦老祖我都看在眼里，这也是老祖考验你的一种方式。\n");
	command("say 这两项工作将决定这门武技的熟练度。\n");

	command("say 血刀刀法中化血诀重要的是要体味以刀放血以及用到的技巧！\n");
	command("say 在密洞之中我留下了一些物事，你去哪儿以血磨刀，看看能否领悟这门绝技！\n");
	command("heng ");
	me->set_temp("quest/xd/xddf/huaxue/asklaozu",1);
	return "化血，以刀化血也是一门奇技！\n";
}

string ask_zujixiake()
{
	object ob, me;
	object daxia;
	object objwhere;
	//mixed str;
	string str,pos;
	int i,j;
	me=this_player();
	ob = this_object();
	
   
	if(me->query("family/family_name")!="血刀门") 
           return "你不是我血刀门弟子，这种门派恩怨你就不要参与了。 ";

//	if (me->query_temp("xd/xdzj"))
//		return "我不是让你去追杀一名偷学我血刀门武技的大侠了么？！\n";

	if ((int)me->query("combat_exp") < 2000000)
		return "你武功未成不足2m，这么危险的任务还是别做了！\n";

	if (me->query("job_name") == "血刀阻击")
		return "你刚做完血刀阻击任务，你自己去修习武功去吧！";

	if(me->query_condition("job_busy"))
		return "你现在正忙着做其他任务呢！";
	if(me->query_condition("xdzj_job"))
		return "你现在正忙着做血刀阻击正派来袭的任务呢！";

	if(me->query_temp("quest/busy")) //added by tangfeng 与quest冲突
		return "现在我这里没有给你的任务，你还是先处理好你其他事情再说吧。";
    
	//定义大侠位置属性
    daxia=new("/d/xuedao/npc/robber");
	daxia->set("long",daxia->query("long")+"\n这是"+me->query("name")+"即将阻击的南方四大正派派来的援兵！\n"NOR);
	//daxia->set("owner",me->query("id"));
	//daxie->set("target",me->query("id"));
	
	daxia->set_temp("target", me->query("id") );
	//调整i的难度系数
	if (me->query("combat_exp")<2000000)
	{
		i=1+random(5);
	}
	else if (me->query("combat_exp")<9600000)
	{
		i=1+random(8);
	}
	else if (me->query("combat_exp")<12600000)
	{
		i=1+random(11);
	}
	else i=1+random(11);
	
	//赋值大侠经验
	daxia->setparty(i,me->query("max_pot")-100,me->query("combat_exp"));
	daxia->apply_condition("npcdie_job",30);
	
	//这里加进去状态
	daxia->copy_player(me);//先初始化npc气血，否则被玩家一下击倒	
	pos=names[random(sizeof(names))];
	if (pos=="") 
	{
		pos=names[1];
	}
	if (!objectp(objwhere=find_object(pos)))
	{
		objwhere=load_object(pos);
	}
//	objwhere = names[random(sizeof(names))];
   // str = objwhere->query("short");

//	if (!objwhere) objwhere=names[1];//赋予初值

	/*	
	for (j=0;j<sizeof(names);j++ )
		{
			objwhere=names[random(sizeof(names))];
			if (objwhere) break; 
			
		}*/
//	str=objwhere->query("short");
	
	message_vision(HIY"$N举手抱拳，对血刀老祖说道，“老祖，弟子请战！”\n"NOR,me);
 
	command("nod "+me->query("id"));
	command("say 月亮快圆了，得下山杀个人祭祭刀了。\n");
	command("say 哼！江南各大门派现在正在陆续向我大血刀派弟子阻击我派发展壮大！\n");
	command("say 照此下去，我派的生存和发展会出现问题！\n");
	
	command("say 老祖我去狙杀他们的领头号称“落花流水”的四大掌门！\n");
	
	command("say 你若有心就替我把那些虾兵蟹将都给我收拾了！\n");
	
  //  if(!objwhere) objwhere = names[random(sizeof(names))];                
    //str = objwhere->query("short");
	if(!objwhere) objwhere =load_object("d/xuedao/wangyougu"); 

	command("say 刚得到门中弟子消息，在血刀门"+objwhere->query("short")+"一带发现一名正在往这儿赶来的所谓“大侠”！\n");
	command("say 我已经打听好了，这名大侠的名字叫“"HIY+daxia->query("name")+"("+daxia->query("id")+NOR")”，可别让他给跑了！\n");

	command("say 大侠，老祖最喜欢干的就是那些大侠，男的直接杀了，把人头给老祖我，女的你知道该怎么做！\n");
	
	command("say 哼！\n");
	
	me->set_temp("xd/xdzj/place",objwhere->query("short"));
	me->set_temp("xd/xdzj/id",daxia->query("id"));
	me->set_temp("xd/xdzj/name",daxia->query("name"));
	me->set_temp("xd/xdzj/time",time());
	me->set_temp("xd/xdzj_job",1);
	daxia->move(objwhere);
	me->apply_condition("xdzj_job", 30 + random(5));
	me->apply_condition("job_busy", 30);
	

	
	return "哼哼。。！\n";
	
}

string ask_xgjz()
{
	object ob, me,obj;
	me=this_player();
	ob = this_object();
	
   
	if(me->query("family/family_name")!="血刀门") 
           return "你不是我血刀门弟子，这种门派恩怨你就不要参与了。 ";

	if (me->query_temp("xd/xgjz_job"))
		return "我不是让你去追杀四大掌门么？？！\n";

	if ((int)me->query_skill("xuedao-daofa",1) < 500)
		return "你血刀刀法武功未成，不足500级，这么危险的任务还是别做了！\n";
	if ((int)me->query_skill("xuedao-jing",1) < 500)
		return "你血刀经武功未成不足500级，这么危险的任务还是别做了！\n";

	if (me->query("job_name") == "雪谷激战")
		return "你刚做完雪谷激战任务，你自己去修习武功去吧！";

	if(me->query_condition("job_busy"))
		return "你现在正忙着做其他任务呢！";
	if(me->query_condition("xgjz_busy"))
		return "你现在正忙着做血刀雪谷激战的任务呢！";

	if(me->query_temp("quest/busy")) //added by tangfeng 与quest冲突
		return "现在我这里没有给你的任务，你还是先处理好你其他事情再说吧。";
    

	
 
	command("pat "+me->query("id"));
	
	command("say 既然你有如此孝心，就替我去狙杀他们的领头号称“落花流水”的四大掌门！\n");

	command("say 这四大门派乃是武林中的高手，都在雪谷一带出没。\n");
	command("say 在哪儿激战比较凶险，你须得尽快修成金刚炼体术方能安然无恙，否则会稍不小心就会憋死！\n");
	
	command("say 哼！这雪谷我已经探究明白，总共分为四层！每一层都有唯一的上下通道\n");
	command("say 你到哪儿后，要仔细观察地形，因我曾经在哪儿爬过，所以应该能找到上下通道(move up/down)！\n");
	command("say 在同一层中可以通过(move east,west,north,south)来前后左右移动！\n");
	command("say 因为在雪中看不到敌人，所以每移动一次都要仔细倾听(ting)敌人的动向。\n");
	command("say 切记不要老是待在一个地方，以防被敌人偷袭。\n");
	command("say 每一层只有一个敌人，杀完后可以继续向下杀去全部杀完，也可以杀一个，但千万不要勉强。\n");
	command("say 四大掌门比较凶残，你一定要小心。\n");

	me->set_temp("xd/xgjz_job",1);
	me->apply_condition("xgjz_job", 30 + random(5));
	me->apply_condition("job_busy", 30);
	if (objectp(obj=present("pi nang",me)))
	{
		destruct(obj);
	}
	obj=new("d/xuedao/obj/pinang");
	obj->set("owner",me->query("id"));
	obj->move(me);
	command("say 我给你一个皮囊，你把杀掉的人头都装入这个皮囊中，回来交付给我！\n");
	
	
	return "哼哼，既然他们自称“落花流水”，那就杀他们个落花流水！！\n";
	
}

int accept_object(object who,object obj)
{
	object obb;
	int exp,pot,exprelife,expdb,exp1;
	string msg;
	int i,j,jobs; 
	
	if (obj->query("kill_by"))
	{
		obb=obj->query("kill_by");
	}
	if (who->query_temp("xuegu/lutianshu")
		||who->query_temp("xuegu/huatiegan")
		||who->query_temp("xuegu/liuchengfeng")
		||who->query_temp("xuegu/shuidai"))
	{
		exp=0;
		pot=0;
		exp1=0;
		jobs=who->query("job_time/雪谷激战");
		//jobs=jobs%50;
		//雪谷激战为50的倍数
	}	
	else if (who->query_temp("xd/xdzj"))
	{
		exp=100+random(20);
		pot=50+random(10);
		jobs=who->query("job_time/血刀阻击");
		//jobs=jobs%10;
		//血刀赤练为10的倍数
	}

	exprelife=0;
	expdb=0;   
	
//如果身份不同奖励不同
	if(!who) return 0;
	

	i=random(who->query("kar"));
	j=20;

	if(who->query("buyvip") )
	{
       exp = exp + exp* 20/ 100;
	   j=18;
	}
	else if(who->query("y-card-vip"))
	{
       exp = exp + exp * 10 / 100;
	    j=15;
	}
	else if(who->query("m-card-vip"))
	{
       exp = exp + exp * 5 / 100;
	    j=10;
	}
	j=random(j);
	
	if (obb
		&& obj->query("name")==who->query_temp("xd/xdzj/name")+"的首级"
		&& obb->query("id")==who->query("id"))
	{
		command("haha "+who->query("id"));
		command("say 你能将"+obj->query("victim_name")+"这个大侠给我杀了，我很高兴！\n");
		command("pat "+who->query("id"));
		command("say 这说明你最近武功修炼不错，我很看好你！\n");
		command("say 你先下去好好休息吧！\n");
		destruct(obj);

		message_vision(RED"\n\n血刀老祖甩手将这颗人头抛向远处，滚落雪坑之中！\n"NOR,who);
	
	//调用奖励系统
	  TASKREWARD_D->get_reward(who,"血刀阻击",-1,0,0,5+j,0,0,0,"血刀老祖");  
	
	/*	
		msg=YEL"血刀老祖回头对你竖起大拇指，随手给了你"+exp+"点经验值和"+pot+"点潜能！\n"NOR;
		//参悟exp
		if(who->query("relife/exp_ext"))
		{
           exprelife=exp*(int)who->query("relife/exp_ext",1) / 20;
		   msg+=YEL"经验参悟期间，你又额外获得"+chinese_number(exprelife)+"点经验值！\n"NOR;

        }

        if(who->query_condition("db_exp")){  
            expdb=exp;
            msg += HIY + "双倍经验奖励期间，你额外地得到了" + HIW + chinese_number(expdb) + HIC + "点" + HIM + "经验！\n"NOR;
        }		
		//上限
		exp=exp+exprelife+expdb;

		if(who->query("combat_exp") > 75000000){
            exp =  exp * 5 /100;
            tell_object(who,"你觉得自己最近心神不宁，对武学的研究已经进入了举步惟艰的程度，似乎就是江湖传说的『"+HIG+"武学障"+NOR+"』。\n");
        }
	//奖励
	*/
		//who->add("combat_exp",exp);
		//who->add("potential",pot);
		
		who->add("job_time/血刀阻击",1);
		who->set("job_name","血刀阻击");
		//message_vision(msg,who);
		//tell_object(who,msg);
	//血刀阻击的人头。
		jobs=who->query("job_time/血刀阻击");
		if (wizardp(who))
			write("jobs="+jobs);
		if (random(who->query("job_time/血刀阻击"))>4000
			&& i > 24
			&& j < 4
			&& !who->query("quest/xd/xddf/chilian/pass")
			&& jobs % 40==0)
		{
			message_vision(HIG"\n血刀老祖冲$N哈哈大笑，说道，“你这个娃娃不错，老祖我很喜欢”！\n"NOR,who,this_object());
			command("pat "+who->query("id"));
			command("say 既然你如此努力，老祖我就将这血刀刀法中赤练神刀绝技传授给你，你听好！\n");
			command("whisper "+who->query("id"));
			message_vision(HBRED"\n$n使出血刀经中之精髓「赤练蛇形」绝技，但见$n右手食指在血刀上一弹，刀花朵朵相辉相映，直袭$N的全身大穴！\n"NOR, who,this_object());
			message_vision(HIC"\n$N顿时吓得半死，但这刀过处，$N手中的兵器寸断数十截！\n"NOR, who,this_object());
			message_vision(HIG"\n$N辛苦修炼血刀刀法，经过$n的这番指引和亲自传授，顿时顿悟!\n"NOR, who,this_object());
			
			message_vision(HBYEL+HIW"恭喜，你如此辛苦努力的工作终于获得老祖认同，并学得赤练神刀绝技！\n！\n"NOR,who);
			command("chat 恭喜"+who->query("name")+"成为我血刀门下又一高手，在实战中修成赤练神刀绝技!\n");
			log_file("quest/xddfchilian", sprintf("%8s(%8s) 失败%d次后，学到血刀刀法中赤练神刀绝技,彻底融会贯通。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
				who->name(1),who->query("id"), who->query("quest/dls/hyd/fail"),i,j,who->query("kar"),who->query("combat_exp")) );
	

			who->set("quest/xd/xddf/chilian/pass",1);
		}
		who->apply_condition("job_busy",2);
		who->apply_condition("xdzj_job",2);
		who->delete_temp("xd/xdzj");
		return 1;	
	}

	
	
//雪谷激战的人头
	if (objectp(obb=obj->query("kill_by"))
		&&who->query_temp("xuegu")
		&&(obj->query("name")=="陆天抒的首级"||obj->query("name")=="花铁干的首级"||obj->query("name")=="刘承风的首级"||obj->query("name")=="水岱的首级")
		&& obb->query("id")==who->query("id"))
	{
		command("haha "+who->query("id"));
		command("say 你能将"+obj->query("victim_name")+"这个所谓的掌门给我杀了，我很高兴！\n");
		command("say 老阻我喜欢干的就是正派掌门！\n");

		command("pat "+who->query("id"));
		command("say 这说明你最近武功修炼不错，我很看好你！\n");
		command("say 你先下去好好休息吧！\n");
		switch (obj->query("name"))
		{
			case "陆天抒的首级":
				if (!who->query_temp("xuegu/lutianshu")) break;				
				exp=200+random(100);
				pot=exp/20;
				exp1=random(10)+15;
				who->delete_temp("xuegu/lutianshu");
				break;
			case "花铁干的首级":
				if (!who->query_temp("xuegu/huatiegan")) break;
				exp=250+random(100);
				pot=exp/20;
				exp1=random(10)+10;
				who->delete_temp("xuegu/huatiegan");
				break;
			case "刘承风的首级":
				if (!who->query_temp("xuegu/liuchengfeng")) break;
				exp=300+random(100);
				pot=exp/20;
				exp1=random(10)+15;
				who->delete_temp("xuegu/liuchengfeng");
				break;
			case "水岱的首级":
				if (!who->query_temp("xuegu/shuidai")) break;
				exp=350+random(100);
				pot=exp/20;
				exp1=random(10)+15;
				who->delete_temp("xuegu/shuidai");
				break;
			
		}

		if(who->query("buyvip") )		
			exp = exp + exp* 20/ 100;
		else if(who->query("y-card-vip"))
		    exp = exp + exp * 10 / 100;
		else if(who->query("m-card-vip"))	
			exp = exp + exp * 5 / 100;


		message_vision(RED"\n\n血刀老祖甩手将"+obj->query("name")+"抛向远处，滚落雪坑之中！\n"NOR,who);
		destruct(obj);

		/*
		msg=YEL"血刀老祖回头对你竖起大拇指，随手给了你"+exp+"点经验值和"+pot+"点潜能！\n"NOR;
		//参悟exp
		if(who->query("relife/exp_ext"))
		{
           exprelife=exp*(int)who->query("relife/exp_ext",1) / 20;
		   msg+=YEL"经验参悟期间，你又额外获得"+chinese_number(exprelife)+"点经验值！\n"NOR;

        }
		//双倍经验奖励
        if(who->query_condition("db_exp")){  
            expdb=exp;
            msg += HIY + "双倍经验奖励期间，你额外地得到了" + HIW + chinese_number(expdb) + HIC + "点" + HIM + "经验！\n"NOR;
        }		
		//上限
		exp=exp+exprelife+expdb;

		if(who->query("combat_exp") > 75000000){
            exp =  exp * 5 /100;
            tell_object(who,"你觉得自己最近心神不宁，对武学的研究已经进入了举步惟艰的程度，似乎就是江湖传说的『"+HIG+"武学障"+NOR+"』。\n");
        }
		*/
	//奖励
		//who->add("combat_exp",exp);
		//who->add("potential",pot);
		TASKREWARD_D->get_reward(who,"雪谷激战",-1,0,0,exp1,0,0,0,"血刀老祖");  
		
		who->add("job_time/雪谷激战",1);
		who->set("job_name","雪谷激战");
		//message_vision(msg,who);
		//tell_object(who,msg);
//血刀阻击的人头。
		if (random(who->query("job_time/雪谷激战"))>4000
			&& i > 20
			&& random(j)<5
			&& random(10)==3
			&& jobs%50==0)
		{
			message_vision(HIG"\n血刀老祖冲你哈哈大笑，说道，“你这个娃娃不错，老祖我很喜欢”！\n"NOR,who);
			command("pat "+who->query("id"));
			command("say 既然你如此努力，老祖我就将这血刀刀法中最高武功秘籍《血刀秘籍》绝技传授给你，你听好！\n");
			command("whisper "+who->query("id"));
			message_vision(HBRED"\n$n使出血刀经中之精髓「血刀大法」绝技，但见$n血刀大法施展后，浑身气血翻涌！\n"NOR, who,this_object());
			message_vision(HIC"\n$n对$N说道，“你可以以后每天都来请教我关于血刀大法的问题了”！\n"NOR, who,this_object());
			
			message_vision(HBYEL+HIW"恭喜，你如此辛苦努力的工作终于获得老祖认同，获得学习《血刀秘籍》的机会！\n！\n"NOR,who);
			who->set("quest/xd/xdj/xuedao/start",1);
			log_file("quest/xdjxuedao", sprintf("%8s(%8s) 得到学习血刀经秘籍的的机会。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
				who->name(1),who->query("id"), who->query("quest/xd/xdj/xuedao/fail"),i,j,who->query("kar"),who->query("combat_exp")) );
		}
		who->apply_condition("job_busy",2);
		who->apply_condition("xgjz_job",2);
		who->delete_temp("xd/xgjz");
		who->delete_temp("xd/xgjz_job");
		return 1;
	}

	
} 
int ask_fail()
{
	object me;
	mapping ob;
	string name;
	me=this_player();
	command("heng "+me->query("id"));
	command("angry "+me->query("id"));

	if (me->query_temp("xd/xdzj"))
	{
		command("say 既然你完不成阻击侠客的任务就暂时下去歇息去了，简直就是废物！。\n");
		me->apply_condition("job_busy",15);
		me->delete_temp("xd/xdzj");
		return 1;
	}
	if (me->query_temp("xd/xgjz")
		||me->query_temp("xd/xgjz_job")
		||me->query_temp("xuegu"))
	{
		command("say 既然你完不成“雪谷激战”的任务就暂时下去歇息去了，简直就是废物！。\n");
		me->apply_condition("job_busy",15);
		me->delete_temp("xd");
		me->delete_temp("xuegu");
	//	me->delete_temp("xd/xdzj");
		return 1;
	}

	command("say 你什么都没做，瞎放弃什么？\n");
	
	me->delete_temp("xd");

	//me->apply_condtion("job_busy",4);

	return 1;
}

void die()
{
	object ob,room;
	ob=this_object();
	room=load_object("d/xueshan/xuegu");

	if (!query_temp("living"))
	{
		ob = new("/kungfu/class/xuedao/laozu");
		ob->move("/d/xueshan/xuegu");
	}
	::die();
}

