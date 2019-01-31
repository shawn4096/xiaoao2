// 陆高轩

inherit F_MASTER;
inherit NPC;
#define	SEAWAR_D	"/d/sld/seawar/seaward"
#include "ansi.h"

int ask_lingpai();
int ask_yaopu();
int ask_yaolu();
int ask_yaozhong();
int ask_makeyao();
int ask_shedu();
string ask_pendu();

string ask_seawar();

void create()
{
	set_name("陆高轩", ({ "lu gaoxuan","lu" }));
	set("long", "他四十来岁年纪，文士打扮，神情和蔼可亲，他是神龙教的护法。\n");
	set("gender", "男性");
	set("title", "神龙教护法");	
	set("age", 42);       

	set("str", 20);
	set("int", 22);
	set("con", 50);
	set("dex", 22);
	set("per", 22);
	
	set("no_ansuan",1);
	set("no_bark",1);
	set("no_quest",1);
	set("no_get",1);

	set("combat_exp", 95000000);
	//set("shen", -5000);
	set("attitude", "peaceful");
	set("max_qi",98500);
	set("max_jing",98500);
	set("neili",98000);
	set("max_neili",98000);
	set("jingli",98000);
	set("eff_jingli",98000);
	set("jiali",200);
	set("score", 2000);

	set_skill("force", 450);
	set_skill("dodge", 450);
	set_skill("parry",450);
	set_skill("strike",450);
	set_skill("throwing",450);
	set_skill("literate",450);
	set_skill("poison",450);
	set_skill("shenlong-yaoli",450);
	set_skill("huagu-mianzhang", 450);
	set_skill("youlong-shenfa",450);
	set_skill("dulong-dafa",450);
	set("startroom","/d/sld/lgxroom");
      
	map_skill("force", "dulong-dafa");
	map_skill("dodge", "youlong-shenfa");
	map_skill("strike", "huagu-mianzhang");
	map_skill("parry","huagu-mianzhang");
	prepare_skill("strike","huagu-mianzhang");
      
	create_family("神龙教",2, "护法");
	set("chat_chance", 2);
	set("chat_msg", ({
		CYN"陆高轩说道：最近药丸制得不多，哎！\n",NOR
		CYN"陆高轩说道：神龙岛兵强马壮，还有罗刹人帮忙，谁都不怕。\n"NOR,
		CYN"陆高轩说道：罗刹人的炮船真是厉害，此战必胜无疑！\n"NOR,
		CYN"陆高轩说道：有洪教主护佑，此战必胜！\n"NOR,
	}) );
	set("inquiry", ([
		"令牌" : (: ask_lingpai :),
		"通行令牌" : (: ask_lingpai :),
		"lingpai" : (: ask_lingpai :),
		"ling pai" : (: ask_lingpai :),
		"冯锡范" : (: ask_shedu :),

		"攻打清军" :	(: ask_seawar() :),
		"job" :		(: ask_seawar() :),
		"护法" :	(: ask_seawar() :),
		"清军" :	"我们正在和清朝水师对峙之中，开来参战吧，好处少不了你的。",
		"喷毒绝技" :	(: ask_pendu() :),
//		"药圃": (: ask_yaopu :), 
//		"炼药": (: ask_makeyao :),
//		"制药": (: ask_makeyao :),
//		"药炉": (: ask_yaolu :),
//		"药种": (: ask_yaozhong :),
	]));

	setup();
	carry_object(__DIR__"obj/changsan")->wear();     
}


void init()
{
	add_action("do_steal","steal");
}

int do_steal(string arg)
{
	object ob=this_object();
	object me=this_player();
	object lpai;

	if(arg!="令牌" && arg!="通行令牌" && arg!="lingpai" && arg!="ling pai")
		return 0;

	if(!living(ob))
		return notify_fail("陆高轩身上现在没有令牌可以偷。\n");

	lpai = present("ling pai", me);
	if(objectp(lpai) &&  lpai->query("sld")) {
		write("你已经有了令牌，还偷它作甚？\n");
		return 1;
	}
	tell_object(me,"你不动声色地靠近陆高轩，偷偷地把手向陆的身上伸去...\n");
	if(me->query("kar") > random(20)) {
		tell_object(me,"你成功地偷到了块通行令牌!\n");
		lpai= new(__DIR__"obj/lingpai");
		lpai->move(me);
	}
	else {
		tell_room(environment(me),CYN"陆高轩高声叫道："+me->name()+"你竟敢偷令牌，不想活了！\n"NOR);
		tell_room(environment(me),CYN"陆高轩一脚把"+me->name()+"踢了出去！\n"NOR);
		if (me->query("qi") > me->query_skill("force",1))
		me->receive_damage("qi",me->query_skill("force", 1));
		else me->set("qi", 1);
		me->move("/d/sld/kongdi");
	}
	return 1;       
}

int prevent_learn(object me, string skill)
{
	return 0;
}

void unconcious()
{
	object ob=this_object();
	object me;
	if (objectp(me=ob->query_temp("last_damage_from")))
	{
		log_file("attack_nokill_npc",sprintf("%s %s偷袭陆高轩。\n", me->query("id"),me->query("name")), me);	
	}
	
	return;
}

int recognize_apprentice(object ob)
{
	mapping myfam;

	myfam = (mapping)ob->query("family");
	if(!(myfam["family_name"] != "神龙教")
	 && ob->query("shen",1) < -10000
	 && ob->query_skill("dulong-dafa",1) >= 100 
	 && ob->query_skill("huagu-mianzhang",1)>=100 ) {
		if(random(10) > 7)
		return 1;
	}
	return 0;
}

int ask_lingpai()
{
	object me,ob,zs;
	mapping myfam;
	object* inv;
	int i;

	me=this_player();
	ob=this_object();
	myfam = (mapping)me->query("family");
	if(!myfam || myfam["family_name"] != "神龙教") {
		return 0;
	}
	inv = all_inventory(me);
	for(i=0; i<sizeof(inv); i++)       
	if(inv[i]->query("id")=="ling pai")
		break;
	if(i>=sizeof(inv)) {
		zs= new(__DIR__"obj/lingpai");
		if (!zs)  return notify_fail("异常错误！\n");
		tell_object(me,"既然你要出岛，我就给你块令牌吧。\n");
		tell_room(environment(me), "陆高轩给" + me->name() + "一块令牌。\n");
		zs->move(me);      
	}
	else {
		tell_object(me,"你不是已经有令牌了么？\n");
	}
	return 1;
}
//ask 药圃
int ask_yaopu()
{
	object me=this_player();
	
	if(!me->query_temp("makeyao",1)) {
		return 0;
	}
	tell_object(me,"陆高轩对你说道：我告诉你一句口诀：先天八卦，顺时而行，辰辰不息，半半相循，乾坤为首，艮兑为尾。\n");
	return 1;
}
//ask about 制药
int ask_makeyao()
{
	object me=this_player();
	mapping myfam;

	myfam = (mapping)me->query("family");
   	if(!myfam || myfam["family_name"] != "神龙教") {
		return notify_fail("你非神龙教，来此作甚？!\n");
   	}
	if(me->query_skill("shenlong-yaoli",1)<101 || me->query_skill("poison",1)<101)
		return notify_fail("你的神龙药理或毒计都不足101级!\n");
	tell_object(me,"陆高轩对你说道：欲炼宝丹，须先埋药种于药圃之中，待其成材后，置于药炉之中，以本教密法炼之即可得药。\n");
	me->set_temp("makeyao",1);
	return 1;
}
//药炉
int ask_yaolu()
{
	object me=this_player();
	object yl;

	if(!me->query_temp("makeyao",1))
   	{
       		return notify_fail("你来此作甚，莫名其妙？!\n");
   	}
	if(objectp(yl=me->query("myyaolu")))
	{
		if(random(10)>2)
			return notify_fail("不是已经给过你药炉了么？\n");
		else
			destruct(yl);
	}
	yl=new("/d/sld/npc/obj/yaolu");
	if(!yl)
		return notify_fail("现在没有药炉，你等会再来要吧。\n");
	else if(!yl->move(me))
	{
		destruct(yl);
		return notify_fail("你先把身上没用的东西处理掉，然后再来要药炉吧。\n");
	}
	else
	{
		yl->set("owner",me);
		tell_object(me,"陆高轩给了你一只药炉，道：拿这只药炉炼药去吧。\n");
		me->set("myyaolu",yl);
	}
	return 1;
}

int ask_yaozhong()
{
	object me=this_player();
	
	if(!me->query_temp("makeyao",1))
   	{
       		return 0;
   	}
	else if(me->query_temp("yaozhong",1))
	{
		return notify_fail("我不是已经跟你说过了么？你怎么又来了！\n");
	}
	tell_object(me,"陆高轩对你说道：我上次不知道把药种塞到哪里去了，等我找到了再给你。\n");
	me->set_temp("yaozhong",1);
	return 1;
}

void kill_ob(object ob)
{
	object me = this_object();
	command("say 老夫正在筹划对抗清军，没功夫陪你玩。");
	me->remove_enemy(ob);
	ob->remove_killer(me);
	ob->add_busy(999);
	command("chat "+ob->query("name")+"("+ob->query("id")+")"+"要杀死我，神龙岛所有弟子要替我报仇啊！\n");
	ob->set_temp("attack/lgx",1);
	//标记，让门派id干掉
	log_file("quest/badmanlist", sprintf("%8s(%8s) 恶意杀死陆高轩，记录在案。\n",ob->name(1),ob->query("id")));
		
	if (ob->query_condition("killer") < 100) ob->apply_condition("killer", 200);
	return;
}

int accept_fight(object ob)
{
	
	ob->add_busy(999);
	ob->set_temp("attack/lgx",1);
	command("chat 老子接受了"+ob->query("name")+"("+ob->query("id")+")"+"的挑战，但若我死了，神龙岛所有弟子要替我报仇啊！\n");

	command("say 老夫正在筹划对抗清军，没功夫陪你玩。");
	log_file("quest/badmanlist", sprintf("%8s(%8s) 恶意fight陆高轩，记录在案。\n",ob->name(1),ob->query("id")));

	return 1;
}

string ask_seawar()
{
	object * team;
	object me;
	int i;
	
	me = this_player();
	team = me->query_team();
	
	if(wizardp(me) && me->query("env/test"))
		return SEAWAR_D->play(me,me,2);
	
	if( sizeof(team) != 2 )
		return "出海参战，你的队伍必须要有两个人。";
	for (i=0;i<sizeof(team);i++) {
		if ( !team[i] || !userp(team[i]) || !present(team[i],environment(me)) )
			return "你要和谁一起出战？";
		if( team[i]->query_condition("job_busy") 
			|| team[i]->query("job_name")=="神龙岛海战" || team[i]->query_condition("killer") )
			return "你们的队伍太忙碌了，休息一会儿再参战吧。";
		if( team[i]->query("combat_exp")<100000 )
			return "你们的队伍的经验太少了，还是先去锻炼一下儿再来参战吧。";
		if( team[i]->query("job_name")=="神龙岛海战" )
			return "你们的队伍的经验太少了，还是先去锻炼一下儿再来参战吧。";

		if( team[i]->query("shen")>-30000 )
			return "你们似乎不是我道中人，我可不放心让你们参战。";
	}

	return SEAWAR_D->play(team[0],team[1],2);
}

int ask_shedu()
{
	object me,ob;
	me=this_player();
	if (!me->query_temp("quest/kl/klz/hongsha/asklu"))
	{
		command("say 你跟我无缘无故，不要聒噪！\n");
		return 1;
	}
	command("consider ");
	command("say 既然是冯锡范老前辈派你来找我，那我就帮你一次!\n");
	command("say 这是给你的一包蝮蛇毒粉，你要拿好了，千万别丢弃了。\n");
	command("say 此物剧毒，切记不易轻易胡乱涂抹(tumo)以免中毒，除非为了修炼某种特殊的功夫。\n");
	ob=new("d/sld/npc/obj/shefen.c");
	ob->move(me);
	me->delete_temp("quest/kl/klz/hongsha/asklu");
	return 1;
}

//面死亡
void die()
{
	object me,ob,room;
	//ob=this_object();
	//room=load_object("d/sld/lgxroom");
	
	if (!query_temp("living")) {
		ob = new("/d/sld/npc/lgx");
		ob->move("/d/sld/lgxroom");
	}
	
	::die();
}

//喷毒绝技
string ask_pendu()
{
	object me;
	int i,j;
	me=this_player();
	if (!me->query("quest/sld/dldf/pendu/start"))
	{
		return "你尚未了解各种药物间相克相生之理，来了也白搭！\n";
	}
	if (me->query_skill("zhiyao",1)<200)
	{
		return "制药术需要达到200大飞阶段方可修习！\n";
	}
	if (me->query_skill("force",1)<450)
	{
		return "基本内功达到450大飞阶段方可修习！\n";
	}
	if (me->query("family/family_name")!="神龙岛")
	{
		return "你并非神龙岛弟子！\n";
	}
	if (time()-me->query("quest/sld/dldf/pendu/time")<86400)
	{
		return "你来的太频繁了！\n";
	}
	if (me->query("quest/sld/dldf/pendu/pass"))
	{
		return "你已经解开这个谜题了！\n";
	}
	command("consider ");
	message_vision(HIY"陆高轩对$N说，“你很不错，竟然能在制药过程中有这么多领悟，看来是可造之材！”\n"NOR,me);

	command("say 我神龙岛最大的特色之一就是对于各种药物的研究。\n");
	command("say 后来穷我一生精力我才发现，倘若将毒素蓄积在体内，然后配合毒龙大法。\n");
	command("say 可以在对战过程中将蓄积的毒药喷射而出，令对方防不胜防。\n");
	command("say 对方一旦中毒，防御力必定大降且受制于药物\n");
	command("say 你若感兴趣我就将这门绝技传授于你！\n");
	
	me->set_temp("quest/sld/dldf/pendu/asklu",1);
	
	command("say 事先声明，你向我请教需要扣除你的门派贡献值每次100点，如果不够你没资格请教我。\n\n\n\n");
	
    command("say 好吧，既然你如此努力，我就告诉你其中诀窍。\n");
    command("whisper "+me->query("id"));
	  
	if (me->is_busy())
	{
	  return "你正在忙碌中!\n";
	}
	me->start_busy(10);
	if (me->query("party/gongji")<100)
	{
		return "你的门派功绩不够\n";
	}
	
	me->add("party/gongji",-100);
	i = 20;
		if(me->query("m-card-vip")) i =  18;
		if(me->query("y-card-vip")) i =  15;
		if(me->query("buyvip"))     i =  10;
		i=random(i);
		j=random(me->query("kar"));
		command("say 你听懂了么。\n");
		command("pat "+me->query("id"));
		if( i<4
			&& me->query("kar")<31
			&& random(me->query_con(1))>35
			&& j > 27 ) 
		{
			tell_object(me,HIC"\n你听了的陆高轩的亲自指点，联想起早期自己制药过程中的种种心得，两下彼此印照，颇有心得。\n"NOR);
			tell_object(me,HIR"\n你按照陆高轩的指点，将蓄积的毒药以毒龙大法运使，忽然间心脉一痛，瞬间领悟了这喷毒剑绝技的运气法门。\n"NOR);
			tell_object(me,HIB"\n你张口喷出一股黝黑的气体，状若蛇矛，约有丈余，闪烁不定！\n"NOR);
			tell_object(me,HIY"\n你历经千辛万苦，终于练成毒龙大法喷毒绝技！\n"NOR);

			me->set("quest/sld/dldf/pendu/pass",1);
			log_file("quest/sldpendu", sprintf("%8s(%8s) 失败%d次后，学到毒龙大法喷毒绝技,彻底融会贯通。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|后天根骨：%d。\n",
				me->name(1),me->query("id"), me->query("quest/sld/dldf/pendu/fail"),i,j,me->query("kar"),me->query_con(1)) );
			command("haha"+me->query("id"));		
			me->delete_temp("quest");
			me->start_busy(2);
			return "恭喜解密喷毒绝技成功!\n";
			
		}	
	   else
		{
			log_file("quest/sldpendu", sprintf("%8s(%8s) 解密喷毒绝技失败%d次！。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
				me->name(1),me->query("id"), me->query("quest/sld/dldf/pendu/fail"),i,j,me->query("kar"),me->query_con(1)) );
			
			tell_object(me,HIY"你听了陆高轩的指点，可是对喷毒绝技的奥妙全然不得要领。\n\n"NOR);
			command("sigh "+me->query("id"));
			command("disapp "+me->query("id"));
			me->add("quest/sld/dldf/pendu/fail",1);
			me->set("quest/sld/dldf/pendu/time",time());
			me->start_busy(2+random(3));
			me->delete_temp("quest");
			me->start_busy(2);
			return "非常遗憾解密喷毒绝技失败"+me->query("quest/sld/dldf/pendu/fail")+"次。\n";
		}

	


}