// /u/beyond/mr/npc/bao.c 包不同
// this is made by beyond
// update 1997.6.24
inherit NPC;
inherit F_MASTER;
#include <ansi.h>
int ask_yusui();

void create()
{
	
	set_name("包不同",({"bao butong","bao","butong"}));
        set("title","金凤庄庄主");
        set("nickname","包三先生");
  	set("long", 
              "他就是慕容复的结拜兄弟姑苏慕容金凤庄的庄主。\n");
        set("age", 25);
	set("attitude", "friendly");
        set("unique", 1);
	set("shen_type", 1);
	set("str", 46);
	set("int", 26);
	set("con", 26);
	set("dex", 26);
	
	set("max_qi", 12500);
	set("max_jing", 5000);
	set("neili", 12500);
	set("max_neili", 12500);
	set("jiali", 200);
	set("combat_exp", 4850000);
	set("score", 85000);

       // set_skill("sword",350);
        set_skill("blade",350);
        set_skill("dodge",350);
        set_skill("force", 350);
		set_skill("shenyuan-gong", 350);
		set_skill("yanling-shenfa", 350);
        set_skill("parry", 350);
        set_skill("murong-daofa", 350);
        set_skill("literate", 130);
       // set_skill("finger", 130);
       // set_skill("canhe-zhi", 130);
        set_skill("strike", 350);
        set_skill("xingyi-zhang", 350);

		map_skill("force", "shenyuan-gong");
        map_skill("strike", "xingyi-zhang");
        //map_skill("finger", "canhe-zhi");
		map_skill("dodge", "yanling-shenfa");
		map_skill("parry", "murong-daofa");
		map_skill("blade", "murong-daofa");  
		//prepare_skill("finger", "canhe-zhi");
        prepare_skill("strike", "xingyi-zhang");
 
       setup();
        carry_object(__DIR__"obj/cloth2")->wear();
         carry_object(__DIR__"obj/blade")->wield();   
        create_family("姑苏慕容",3,"弟子");
        set("inquiry", ([
            "name" : "非也，非也，我就是姑苏慕容金凤庄庄庄主包不同。\n",
            "here" : "这里是大名鼎鼎的燕子坞，难道你没有听说过？\n",
            "rumors" : "慕容公子的以彼之道，还施彼身天下闻名。\n",
            "阿珠" : "阿珠住在听香水榭，是慕容公子的贴身丫鬟，跟阿碧两个人一同侍奉公子。\n",
            "阿碧" : "阿碧姑娘住在琴韵小筑，所有要拜见慕容公子的人都要由她那里经过。\n",
            "王语嫣" : "王姑娘是慕容公子的表妹，不知道什么时候他们成亲。\n",
            "邓百川" : "邓百川是我大哥，是燕子坞青云庄的庄主。\n",
            "公孙乾" : "公孙乾是我二哥，是燕子坞赤霞庄的庄主。\n",
            "风波恶" : "风波恶是我四弟，是燕子坞玄霜庄的庄主，他就是喜欢跟别人打架。\n",
            "听香水榭" : "听香水榭是阿珠姑娘住的地方，离这里不远。\n",
            "琴韵小筑" : "琴韵小筑是阿碧姑娘住的地方，坐小舟有三九水路就到了。\n",
            "曼佗罗山庄" : "曼佗罗山庄是公子的姑妈住的地方，平时连我都不敢去。\n",
            "还施水阁" : "这是燕子坞的秘密之所在，我可不便对你说。\n",   
			"玉碎刀光绝技":   (: ask_yusui :),

       ]));
}

void attempt_apprentice(object ob)
{
    if (ob->query_skill("shenyuan-gong",1)<100)
    {
		command("say 我慕容最重视内功修为，你神元功不足100，还是努力修炼去吧。\n");
    }
	command("say 嗯，看你还是个学武的料，我就收下你吧！");
	command("recruit " + ob->query("id"));
	ob->set("title","姑苏慕容第四代弟子");
}
int ask_yusui()
{
	int i,j;
	object me=this_player();
	if (me->query("family/family_name")!="姑苏慕容")
	{
		command("say 你不是我姑苏南慕容的人，来此瞎打听什么？\n");
		return 1;
	}
	if (me->query_skill("murong-daofa",1)<200)
	{
		command("say 你的慕容刀法不足200，说了你也不懂？\n");
		return 1;
	}
	if (time()-me->query("quest/mr/mrdf/yusui/time")<86400)
	{
		command("say 你来的太频繁了？\n");
		return 1;
	}
	if (me->query("quest/mr/mrdf/yusui/pass"))
	{
		command("say 你已经解开了？\n");
		return 1;
	}

    j = 20;
    if(me->query("m-card-vip")) j =  18;
    if(me->query("y-card-vip")) j =  15;
    if(me->query("buyvip"))     j =  10;
	i= random(j);
	command("say 我南慕容的慕容刀法乃是在实战中总结出来的武技，极具攻击性！\n");
	command("say 想当初我大燕国东征西讨，南征北战，这刀法曾立下汗马功劳！\n");
	message_vision(HIC"\t\t包不同说道："HIY"劈天盖地满壮志!\n"NOR,me);
	message_vision(HIC"\t\t包不同说道："HIR"弯刀逆转倒乾坤!\n"NOR,me);
	message_vision(HIC"\t\t包不同说道："HIG"遥看万疆千里雪!\n"NOR,me);
	message_vision(HIC"\t\t包不同说道："HIM"壮志豪气满江湖!\n"NOR,me);
	command("say 想想这首歌诀就令人血脉愤张！\n");
	command("say 你懂得了这首歌诀的要义也就懂得了这门刀法真意义！\n");
	command("say 既然你想学，我就说给你听听，能否领悟就看你的悟性了，你听好了！\n");
	me->start_busy(2);
	if (i<7
		&&me->query("kar")>25)
	{
		message_vision(HIY"$N听着包不同的讲解，看着他满腔激昂的讲解，你忽然明白了这慕容刀法的真正意义！\n"NOR,me);
		message_vision(HIG"那就是一往无前的一种气势！忍不住随声吟道·············\n"NOR,me);
		message_vision(HIY"\t\t劈天盖地满壮志!\n"NOR,me);
		message_vision(HIR"\t\t弯刀逆转倒乾坤!\n"NOR,me);
		message_vision(HIG"\t\t遥看万疆千里雪!\n"NOR,me);
		message_vision(HIM"\t\t壮志豪气满江湖!\n"NOR,me);

		message_vision(HIY"$N的声音越来越大，声震云霄，随后喃喃自语道，”宁为玉碎，不为瓦全！“\n"NOR,me);
		message_vision(HIG"包不同听你说了这句话，忽然间仰天长啸！！\n"NOR,me,this_object());
		command("shout 我大慕容又添了一员虎将！何愁复兴我大燕！\n");
		command("chat 江湖人云，”北乔峰，南慕容“，我大慕容今日喜获良才，我先浮一大白！\n");
		command("chat* congra "+me->query("id"));

		command("chat* laught "+me->query("id"));
		me->set("quest/mr/mrdf/yusui/pass",1);
		log_file("quest/mrdfyusui",sprintf("%-18s失败%s次后，成功从包不同处领悟玉碎刀光绝技的精髓所在，福：%d，悟：%d。\n",
			me->name(1)+"("+capitalize(getuid(me))+")",
			chinese_number(me->query("quest/mr/mrdf/yusui/fail")), 
			me->query("kar"), 
			me->query("int")), me);
		return 1;
	}else {

		command("sigh " + me->query("id"));
		command("poor "+ me->query("id"));
		command("disapp "+ me->query("id"));

		command("say 看来你还是未到明白其中奥妙所在的时候,明天再来吧!");
		message_vision(HIG"\n\n$N参悟慕容刀法的玉碎刀光失败！！\n"NOR,me,this_object());

		me->add("quest/mr/mrdf/yusui/fail", 1);
		me->set("quest/mr/mrdf/yusui/time", time());
		log_file("quest/mrdfyusui",
			sprintf("%-18s想从包不同处领悟玉碎刀光绝技的精髓失败，失败%s次。\n",
				me->name(1)+"("+capitalize(getuid(me))+")",
				chinese_number(me->query("quest/mr/mrdf/yusui/fail")) 
			), me);
	
		me->start_busy(1);
	}
	return 1;
/**/
}