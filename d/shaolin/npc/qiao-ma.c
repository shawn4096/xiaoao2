// lao-qiao.c 乔三槐

inherit NPC;
#include <ansi.h>
int ask_job();
int ask_over();

void create()
{
	set_name("乔大妈", ({ "qiao dama", "qiao" , "dama"}));
	set("gender", "女性");
	set("age", 55 );
	set("long",
		"她是江湖好汉“北乔峰”的母亲，面色慈祥，甚是亲和。\n"
	);
	set_skill("unarmed", 20);
	set_skill("dodge", 20);
	set("qi", 400);
	set("max_qi", 400);
	set("eff_qi", 400);
	set("jing", 300);
	set("max_jing", 300);
	set("inquiry", 
                ([
                       "喂猪" : (: ask_job :),
                        "结束" : (: ask_over :),
                    
                ]));
	setup();

}

int ask_job()
{
	object me,shi;

	me=this_player();
	if (!me->query_temp("sljob/qingwu/weizhu"))
	{	
		command("say 你无缘无故不要来调戏老娘！\n");
		return 1;
	}

	if (me->query_temp("sljob/weizhu/askqiao"))
	{	
		command("say 你不是已经领了猪食去喂猪了么？\n");
		return 1;
	}
	if (me->is_busy()||me->is_fighting()||me->query_condition("job_busy"))
	{
		command("say 你现在正在忙乱中，待会再来！\n");
		return 1;
	}
	if (objectp(shi=present("zhu shi",me)))
	{
		command("say 你已经领了猪食，还不去喂猪？\n");
		return 1;
	}
	message_vision("$N对$n说道，既然是清无比丘派你来的，你就去猪舍喂养吧\n唉！我们家那死老头子不知道死哪儿去了，我身体不好，猪都快要饿死了！\n",this_object(),me);
	shi=new("d/shaolin/npc/obj/zhushi");
	shi->move(me);
	me->set_temp("sljob/weizhu/askqiao",1);
	command("say 最近世道不太安定，也不知道我们家峰儿现在怎么样，真人令人揪心！\n");
//	command("say 把这猪养肥了，等峰儿回来就可以杀了吃了！\n");
	return 1;
}
int ask_over()
{
	object me,shi;

	me=this_player();
	if (!me->query_temp("sljob/weizhu/over"))
	{
		command("say 你又开始偷懒，为啥不将猪彻底喂完？\n");
		return 1;
	}
	if (objectp(shi=present("zhu shi",me)))
	{
		command("say 你已经领了猪食，还不去喂猪？\n");
		return 1;
	}
    message_vision("$N对$n说道，猪已经喂饱了，真是麻烦你了，你回去后跟清无大师表示感谢！\n",this_object(),me);
	


	me->delete_temp("sljob/weizhu");
//	command("say 最近世道不太安定，也不知道我们家峰儿现在怎么样，真人令人揪心！\n");
	command("say 把这猪养肥了，等峰儿回来就可以杀了吃了！\n");
	//判断可以推荐回去

	me->set_temp("sljob/qingwu/weizhuok",1);

	return 1;
}
