// 苏荃
// lane 2004.12.24 add 福利

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
int ask_zhushao();
void destructing(object ob);



string ask_houshan();
string ask_me();
string ask_skill();
string ask_chansishou();
string ask_beauty();
string ask_shedujing();
int do_meihuo();

int ask_gold();

void create()
{
	set_name("苏荃", ({ "su quan","su" }));
	set("long", "她看模样不过二十三四岁，是一个美貌少妇，微微一笑，更是媚态横生，\n艳丽无匹，她是神龙教教主的夫人。\n");
	set("gender", "女性");
        set("title", "神龙教教主夫人");
        set("age", 23);
        set("str", 22);
        set("int", 32);
        set("con", 22);
        set("dex", 38);
        set("per", 50);
        set("combat_exp", 125000000);
        set("shen", -10000);
        set("attitude", "peaceful");
        set("max_qi",29000);
        set("max_jing",8000);
        set("neili",29000);
        set("max_neili",29000);
        set("jingli",7800);
        set("eff_jingli",7800);
        set("jiali",200);
        set("score", 15000);
        set("yaoli_count",1);

	set_skill("force", 450);
	set_skill("dodge", 450);
	set_skill("parry",450);
	set_skill("hand",460);
	set_skill("chansi-shou", 460);
	set_skill("youlong-shenfa",450);
	set_skill("dulong-dafa",450);
	set_skill("dagger",480);
	set_skill("tenglong-bifa",480);
	set_skill("leg",460);
	set_skill("shenlong-tuifa",460);

	map_skill("force", "dulong-dafa");
	map_skill("dodge", "youlong-shenfa");
	map_skill("hand", "chansi-shou");
	map_skill("dagger","tenglong-bifa");
	map_skill("parry","tenglong-bifa");
	map_skill("leg","shenlong-tuifa");
	prepare_skill("hand","chansi-shou");

	set_temp("apply/damage", 88);
	set_temp("apply/dodge", 188);
	set_temp("apply/attack", 188);
	set_temp("apply/armor", 388);
	
	set("chat_chance_combat", 60);
	set("chat_msg_combat", ({
		(: perform_action, "hand.chansi" :) ,
		(: perform_action, "hand.tuxin" :) ,
		(: perform_action, "hand.luanwu" :) ,
		(: perform_action, "dagger.beauty" :) ,
		(: perform_action, "dagger.guifei" :) ,
		(: perform_action, "dagger.xiaolian" :) ,
		(: perform_action, "dagger.feiyan" :) ,
		(: exert_function, "wudi" :) ,
		(: exert_function, "shexin" :) ,
		(: exert_function, "pendu" :) ,
	}));      
	set("inquiry", ([
		"资金" : (: ask_gold :),
		"竹哨" : (: ask_zhushao :),
		"蛇毒经" : (: ask_shedujing :),
		"zhushao" : (: ask_zhushao :),
		"仙福居": (: ask_houshan() :),
		"神龙药理经" : (: ask_me :),
		"魅惑绝技" : (: do_meihuo :),
		"贵妃回眸" :(:ask_skill:),
		"金蛇缠丝手" :(:ask_chansishou:),
		"美人三招" :(:ask_beauty:),
	]) );

	set("chat_chance", 3);
	set("chat_msg", ({
		"苏荃自言自语道：玄铁匕首虽然不错，但毕竟不够锋利，唉！\n",
	}));

	create_family("神龙教",1, "教主夫人");
	setup();
	carry_object("d/sld/npc/obj/skirt")->wear();
	carry_object(BINGQI_D("dagger/sld_bishou"))->wield();
}
string ask_shedujing()
{
	object me=this_player();
	object book;
	if (me->query("faminly/family_name")!="神龙教" ||me->query("generation")>2)
	{
		command("你在我教中辈分太低，还是好好修炼，功力太弱，你控制不了毒性，容易走火入魔。\n");
		command("pat "+me->query("id"));
		return "好好干，我教当大兴！";
	}
	book=new("d/sld/obj/shedujing");
	book->move(me);
	command("blush");
	return "这本经书你可要拿好了，流落在外教主定不会饶你。若修习得当，教主当另有所赐。\n";

}
void attempt_apprentice(object ob)
{
       mapping myfam;

       myfam = (mapping)ob->query("family");
 	   if(!myfam || myfam["family_name"] != "神龙教")
           command("say 你非本教弟子，还是先去向黑龙使求教吧.");
       else if(ob->query("shen",1) > -1500000)
           command("say 你还不够心黑手辣,不足1.5m负神，再去多杀几个白道中人吧");
       else if(ob->query_skill("dulong-dafa",1)<250)
       {
			command("say 毒龙大法不足250，别来找我。");
            command("shake "+ob->query("id"));
	   }
       else
            {
           command("say 好吧，我就收下你做我的弟子。");
	    command("recruit " + ob->query("id"));
       }
	return;	
}
int accept_object(object me, object ob)
{
	object obj,su;
	su=this_object();
	if (ob->query("id")!="shenlong gou")
	{
	
		if( ob->query("weapon_prop/damage") >= 80){
		obj=unew(BINGQI_D("xtbs"));
		if(obj) {
			obj->move(me);
			tell_object(me,"你能如此忠心，真是太好了，这把玄铁匕首就赏给你吧！\n");
			tell_room(environment(me), "苏荃给" + me->name() + "一柄玄铁匕首。\n");
		}
		else {
			tell_object(me,"你能如此忠心，真是太好了，教主不会亏待你的！\n");
			me->add("shen", -(3000+random(1000)));
		}
		call_out("destructing", 0, ob);
		return 1;
		}
	}else { 
		if (me->query_temp("clgf/asksu1")
		&& objectp(present("shenlong gou",me)))
		{
			message_vision(HIC"$N恭恭敬敬地递给$n一柄"+ob->query("name")+"\n"NOR,me,su);
			ob->move(su);
			message_vision(HIC"$n举起白皙的细长手指，轻轻抚摸"+ob->query("name")+"，笑道，真是一柄好兵器。\n看你这么用心，这兵器反正我也用不着，就送给你了。\n"NOR,me,su);
			ob->move(me);
			me->set_temp("clgf/suok",1);
			message_vision(HIC"$n一挥手，一股大力传来，将$N送入一处山清水秀之地。\n"NOR,me,su);

			me->move("d/sld/xfj");
		}
	}
	return 0;
}

void destructing(object ob)
{
	if(ob)
	destruct(ob);
}

int ask_zhushao()
{
	object me,ob,zs;
	mapping myfam;
	object* inv;
	int i;

	me = this_player();
	ob = this_object();
	myfam = (mapping)me->query("family");
	if(!myfam || myfam["family_name"] != "神龙教") return 0;
	if(me->query("combat_exp") < 2000000) {
		command("say 我现在可不能给你竹哨哦。");
		return 1;
	}

	inv = all_inventory(me);
	for(i=0; i<sizeof(inv); i++) {
		if(inv[i]->query("id")=="zhushao") {
			tell_object(me,"你不是已经有竹哨了么？\n");
			return 1;
		}
	}

	zs = new("d/sld/npc/obj/zhushao");
	if (!zs)  return notify_fail("异常错误！\n");
	zs->set("owner",me);

	tell_object(me,"好吧，我给你个竹哨，可不要弄丢了。\n");
	tell_room(environment(me), "苏荃给" + me->name() + "一个竹哨。\n");
	zs->move(me);

	return 1;
}

string ask_me()
{
	object ob;
	mapping fam;
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "神龙教")
		return RANK_D->query_respect(this_player()) + "与本派素无来往，不知此话从何谈起？";

	if ( this_player()->query_temp("ask_slylj") )
		return "刚刚不是给你了嘛。";
	ob=unew("/clone/book/slyaoli-book.c");

	if(!clonep(ob)) return "你来晚了，那本书我已经给别人了。";
	if(clonep(ob) && ob->violate_unique())
	{
		destruct(ob);
		return "你来晚了，那本书我已经给别人了。";
    }
	ob->move(this_player());
	this_player()->set_temp("ask_slylj", 1);
	message_vision("苏荃从怀中掏出一本神龙药理经递给$N。\n",this_player());
	return "这本书是我和陆先生借来看看的，你拿去可要好好研究啊。";
}
/*
string ask_houshan()
{
	object me=this_player();
	if (me->query_temp("clgf",))
	{
	}
	int lvl = (int)me->query_skill("shenlong-yaoli", 1);
	if ( lvl < 120 ) return "仙福居乃我派逍遥胜地,你的神龙药理还不到120，你还不够资格去。";
	if ( file_name(environment(this_object())) != this_object()->query("startroom"))
		return "等我回神龙岛再说吧。";
	tell_object(me, "那可是个好地方，山清水秀，意境无穷，既然你问到了，那我就带你去吧。\n");
	me->set_temp("clgf/clasksu",1);
	me->move("/d/sld/xfj");
	return "又一个好苗子。";
}*/

string ask_houshan()
{
	object me=this_player();
	int lvl = (int)me->query_skill("shenlong-yaoli", 1);

//	if (!me->query_temp("clgf/askhong"))
//	{
//		return "没有教主严令，谁都不能传授此绝技。\n";
//	}

	if ( lvl < 120 ) return "仙福居乃我派逍遥胜地,你的神龙药理还不到120，你还不够资格去。";
	
	if ( file_name(environment(this_object())) != this_object()->query("startroom"))
		return "等我回神龙岛再说吧。";
	command("say 哪儿是个好地方，山清水秀，春光明媚，乃是我神龙岛最好的所在。\n");
	command("say 前一阵子和教主曾住在哪儿，真是好地方......\n");

	tell_object(me, "唉，不知道为什么，苏荃似乎有些难言之隐。\n");
	
	me->set_temp("clgf/asksu1",1);
	me->delete_temp("clgf/askhong");
	return "既然教主有令，那么你就给我去找到我神龙岛的传说中的宝钩吧，找到了我就把带你过去。\n";
}

string ask_skill()
{
	object me=this_player();
	mapping myfam;
			
	myfam = (mapping)me->query("family");
	if(!myfam || myfam["family_name"] != "神龙教") return 0;
	if(me->query_skill("tenglong-bifa",1)<100) return 0;
	if(me->query("sld/guifei") || me->query_skill("tenglong-bifa",1)<150)
		return "你不是已经会贵妃回眸了么？";
	command("giggle");
	command("whisper "+getuid(me)+" 其实贵妃回眸这招还有别的精要之处，大致是这样的。。。。");
	me->set("quest/sld/tlbf/guifei",1);
	tell_object(me,HIW"你听着苏荃的指点，不住点头，渐渐就明白了贵妃回眸这一招的精要。\n"NOR);
	return "大致上就是这样了，本教武功虽不重攻击，但往往越战越强，所向披靡。";
}

int ask_gold()
{
	object me;
	int skill, gold;
	mapping myfam;
	me = this_player();
	skill = me->query_skill("dulong-dafa", 1);
	myfam = (mapping)me->query("family");

	if( !myfam || myfam["family_name"] != "神龙教" ) {
		command("sneer "+(string)me->query("id"));
		command("say 看"+ RANK_D->query_respect(me) +"面生得很呀，是不是考虑下加入我教啊？");
		return 1;
	}

	if( (int)me->query("sld_given") >= (int)me->query("age") ) {
		command("sigh "+(string)me->query("id"));
		command("say 你今年不是已经拿了钱了吗？明年再来吧。");
		return 1;
	}

	if( (int)me->query("age") < 18 || skill < 100 ) {
		command("interest");
		command("say "+ RANK_D->query_respect(me) +"年纪轻轻，来我教不久，还是安心学武吧。\n");
		return 1;
	}

	gold = 300000 + skill * 5000;
	if( 100 >= skill ) gold += gold/2;
	me->add("balance", gold);
	me->set("sld_given", (int)me->query("age"));
	command("say 我教白龙使在朝廷中也是个有身份的人，资金当然不会匮乏！");
	command("say 我将这" + MONEY_D->money_str(gold) + "存入你的钱庄，你离岛后可要好好为我教办事啊！");
	return 1;
}

string ask_chansishou()
{
	object me=this_player();
	mapping myfam;
			
	myfam = (mapping)me->query("family");
	if(!myfam || myfam["family_name"] != "神龙教") 
		return "你非我教人员，来此作甚？\n";
	if(me->query_skill("dulong-dafa",1)<250) 
		return "你的毒龙大法等级不足250级，功力高后再来。\n";
	if(me->query("gender")=="男性") 
		return "我只喜欢女性玩家，男性玩家找教主去。\n";
	if(me->query("quest/sld/chss/pass"))
		return "你的缠丝手奥秘不是已经领会了么？\n";
	command("giggle");
	command("smile");
	command("blush");
	command("smile");
	command("giggle");
	command("whisper "+getuid(me)+" 其实金蛇缠丝手这招还有别的精要之处，大致是这样的。。。。");
	me->set_temp("chansi/asksu",1);
	
	tell_object(me,HIW"你听着苏荃的指点，不住点头，渐渐就明白了金蛇缠丝手这一招的精要。\n"NOR);
	return "\n\n本教武功重在实践，很多武技都是从岛上神龙所参悟而来，要想完整理解这招。\n"+
		"\n你最好能到山下的树林中去观察各种蛇的动作，这样才能对这金蛇缠丝手理解更透彻！\n";
}

int do_meihuo()
{	
	object me = this_player();
	//int i=3+random(3);
	me->start_busy(1);
	if (me->query("family/family_name") != "神龙教" ){
		command("say 你不是我神龙教中人士来此作甚？\n");
		return 1;
	}
	if (me->query("family/master_id")!="su quan"||me->query("family/master_name")!="苏荃")
	{
		command("say 我记得没有这个弟子啊？\n");
		return 1;
	}
    if (me->query("quest/sld/tlbf/meihuo/pass")){
		command("say 你已经开了这个谜题还来此作甚？？\n");        	
		return 1;				
	}
	if (me->query("gender")!="女性"){
		command("say 唉！腾龙匕法这功夫，我看男人们就算了？？\n");        	
		return 1;				
	}
	if (time()-me->query("quest/sld/tlbf/meihuo/time")<86400){
		command("say 你也太勤快点了耶？？\n");        	
		return 1;				
	}
		    command("sigh ");
			command("我虽然贵为教主夫人，可是....");
			command("sigh ");
			command("sigh ");
			command("blush ");
			message_vision(HIY"\n\n苏荃一时间不知道想起了什么，脸上红一阵，白一阵，似乎甚是羞怒又似乎是难以启齿之状。\n"NOR,me);
			command("sigh ");
			command("say 这魅惑之武技，说起来也没什么，只不过凭借女的本能罢了。\n");
		    command("say 尤其是漂亮的女人施展出来效果很不错。\n");
			command("say 你若有心我就指点你点，能否领悟得了就看你的水平了。\n\n\n");
			//me->set_temp("tlbf/asksu",1);
			message_vision(HIR"\n\n$N恭恭敬敬地向苏荃请教关于腾龙匕法魅惑的绝技。\n"NOR,me);
			me->start_busy(999);
			remove_call_out("thinking");
			call_out("thinking",1,me);
		return 1;

			
}

int thinking(object me)
{
  int i,j; 
  if(!me) return 0;
  i=random(me->query("kar"));
  j=random(10);
  me->set("quest/sld/tlbf/meihuo/time",time());
  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) 参悟腾龙匕法魅惑时，KAR异常，当前经验：%d。年龄：%d。kar:%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("canwu_meihuo")<(30+random(10)))
   {  
	  me->add_temp("canwu_meihuo",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n你仔细聆听师傅的讲述，将师傅所传授的心法彼此印证，只觉得耳目一新...\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n忽然，你似乎抓住了一些明悟。\n"NOR);
			break;
		case 2:
			 tell_object(me,HIR"\n你陷入馄饨状态，大脑一片空明，似乎要抓住那个线索了！..\n"NOR);
			break;
		case 3:
			tell_object(me,HIW"\n你枯坐哪儿，甚是无聊，神情抑郁，似乎有些累了.\n"NOR);
			break;
		case 4:
			tell_object(me,CYN"\n你自言自语，神情疲倦之际，似乎遇到瓶颈了..\n"NOR);
			break;
		case 5:
			tell_object(me,MAG"\n你思维漂浮在空中，宛如婴儿沐浴.神清气爽.\n"NOR);
			break;
		default:tell_object(me,YEL"\n你叹了一口气，精神总是不能有效集中.\n"NOR);
			break;

	  }
      

	  tell_room(environment(me),HIC"\n"+me->query("name")+"面色平和，浑然忘我，似乎在思索着什么...\n"NOR, ({}));

	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);

   } 
   else if (i>=20
			&& j>5
			&& me->query("kar")<31)
 	{ 
        
         me->start_busy(3);     
         message_vision(HIY"\n$N「噗嗤」一声笑了起来，说道：“原来是这样啊，难怪。。。。”\n"NOR,me); 
		 message_vision(HIY"\n$N 终于得知教主是因为了修炼了一种神奇的功夫，居然不能人道，难怪教主夫人会如此。\n"NOR,me); 
         message_vision(HIY"\n$N心下恍悟，终于领悟了苏荃所传授的腾龙匕法这魅惑的奥秘！”\n"NOR,me); 
         log_file("quest/tlbfmeihuo", sprintf("%s(%s) 解密成功！第%d次参悟，机缘巧合下，成功参悟腾龙匕法魅惑绝技的奥秘，当前幸运值：%d,当前随机值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/sld/tlbf/meihuo/fail"),
		 i,
		 j,
         me->query("combat_exp")));

		 me->set("quest/sld/tlbf/meihuo/time",time());
		 me->set("quest/sld/tlbf/meihuo/pass",1);
		 me->delete_temp("canwu_meihuo");
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N长叹一生，自言自语地说道：“羞死人了，居然要这样去展示女人魅力，我不想活了。”\n"NOR,me); 
		 message_vision(HIY"\n参悟腾龙匕法魅惑绝技解密失败！\n"NOR,me); 
         log_file("quest/tlbfmeihuo", sprintf("%s(%s) 失败！第%d次失败参悟腾龙匕法魅惑绝技，当前幸运值：%d,当前随机值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/sld/tlbf/meihuo/fail",1),
		 i,
		 j,
         me->query("combat_exp")));
        
		 me->add("quest/sld/tlbf/meihuo/fail",1);
		 me->set("quest/sld/tlbf/meihuo/time",time());
		 me->start_busy(2);
		 me->delete_temp("canwu_meihuo");
		 return 1;
   }

}

string ask_beauty()
{	
	object me = this_player();
	//int i=3+random(3);
	me->start_busy(1);
	if (me->query("family/family_name") != "神龙教" )
	{
		command("say 你不是我神龙教中人士来此作甚？\n");
		return "";
	}
	if (me->query("family/master_id")!="su quan"||me->query("family/master_name")!="苏荃")
	{
		command("say 我记得没有这个弟子啊？\n");
		return "";
	}
    if (me->query("quest/sld/tlbf/beauty/pass")){
		command("say 你已经开了美人三招这个谜题了么，还来此作甚？？\n");        	
		return "";				
	}
	if (me->query("gender")!="女性"){
		command("say 唉！腾龙匕法这功夫，我看男人们就算了？？\n");        	
		return "";				
	}
	if (time()-me->query("quest/sld/tlbf/beauty/time")<86400){
		command("say 你也太勤快点了耶？？\n");        	
		return "";				
	}
		    command("giggle ");
			command("这是教主当初传下来的武技，神鬼难测.");
			command("giggle ");
			command("giggle ");
			command("giggle ");
			message_vision(HBMAG+HIW"$N乘$n稍稍走神之机，将腾龙匕法的招式融会贯通，以「美人三招」的方式施展出来。\n"NOR,this_object(),me);
			message_vision(HBMAG+HIW"$N手中的匕首寒光闪闪，正是一招「贵妃回眸」！\n"NOR,this_object());
			message_vision(HIR"$N过程中夹杂着神龙腿法「裙底腿」连环踢出！\n"NOR,this_object());

		    message_vision(HBMAG+HIW"$N又是一招「小怜横陈」顺势而出！\n"NOR,this_object());
			message_vision(HIC"$N过程中夹杂着缠丝手「金蛇缠丝」！\n"NOR,this_object());
			message_vision(HBMAG+HIW"$N又是一招「飞燕回翔」！\n"NOR,this_object());

			command("say 你若有心我就指点你，能否领悟得了就看你的水平了。\n\n\n");
			//me->set_temp("tlbf/asksu",1);
			message_vision(HIR"\n\n$N恭恭敬敬地向苏荃请教关于腾龙匕法魅惑的绝技。\n"NOR,me);
			me->start_busy(999);
			remove_call_out("thinking_bt");
			call_out("thinking_bt",1,me);
		return "";
			
}


int thinking_bt(object me)
{
  int i,j; 
  if(!me) return 0;
  i=random(me->query("kar"));
  j=random(20);
  me->set("quest/sld/tlbf/beauty/time",time());
  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) 参悟腾龙匕法美人三招时，KAR异常，当前经验：%d。年龄：%d。kar:%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("canwu_bt")<(20+random(10)))
   {  
	  me->add_temp("canwu_bt",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n你仔细聆听师傅的讲述，将师傅所传授的心法彼此印证，只觉得耳目一新...\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n忽然，你似乎抓住了一些明悟。\n"NOR);
			break;
		case 2:
			 tell_object(me,HIR"\n你陷入馄饨状态，大脑一片空明，似乎要抓住那个线索了！..\n"NOR);
			break;
		case 3:
			tell_object(me,HIW"\n你枯坐哪儿，甚是无聊，神情抑郁，似乎有些累了.\n"NOR);
			break;
		case 4:
			tell_object(me,CYN"\n你自言自语，神情疲倦之际，似乎遇到瓶颈了..\n"NOR);
			break;
		case 5:
			tell_object(me,MAG"\n你思维漂浮在空中，宛如婴儿沐浴.神清气爽.\n"NOR);
			break;
		default:tell_object(me,YEL"\n你叹了一口气，精神总是不能有效集中.\n"NOR);
			break;
	  }
      
	  tell_room(environment(me),HIC"\n"+me->query("name")+"面色平和，浑然忘我，似乎在思索着什么...\n"NOR, ({}));

	  remove_call_out("thinking_bt");
	  call_out("thinking_bt",3+random(3), me);

   } 
   else if (i>=25
			&& j<3
			&& me->query("kar")<31)
 	{ 
        
         me->start_busy(3);     
         message_vision(HIY"\n$N「噗嗤」一声笑了起来，说道：“原来是这样啊，难怪。。。。”\n"NOR,me); 
		 //message_vision(HIY"\n$N 终于得知教主是因为了修炼了一种神奇的功夫，居然不能人道，难怪教主夫人会如此。\n"NOR,me); 
         message_vision(HIY"\n$N心下恍悟，终于领悟了苏荃所传授的腾龙匕法这【美人三招】的奥秘！”\n"NOR,me); 
         log_file("quest/tlbfbeauty", sprintf("%s(%s) 解密成功！第%d次参悟，机缘巧合下，成功参悟腾龙匕法美人三招绝技的奥秘，当前幸运值：%d,当前随机值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/sld/tlbf/beauty/fail"),
		 i,
		 j,
         me->query("combat_exp")));

		 me->set("quest/sld/tlbf/beauty/time",time());
		 me->set("quest/sld/tlbf/beauty/pass",1);
		 me->delete_temp("canwu_bt");
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N长叹一生，自言自语地说道：“这腾龙匕法的终极绝技竟然如此难。”\n"NOR,me); 
		 message_vision(HIY"\n参悟腾龙匕法美人三招绝技解密失败！\n"NOR,me); 
         log_file("quest/tlbfbeauty", sprintf("%s(%s) 失败！第%d次失败参悟腾龙匕法美人三招绝技，当前幸运值：%d,当前随机值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/sld/tlbf/beauty/fail",1),
		 i,
		 j,
         me->query("combat_exp")));
        
		 me->add("quest/sld/tlbf/beauty/fail",1);
		 me->set("quest/sld/tlbf/beauty/time",time());
		 me->start_busy(2);
		 me->delete_temp("canwu_bt");
		 return 1;
   }

}