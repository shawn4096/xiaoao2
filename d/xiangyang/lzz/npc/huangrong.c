// /d/thd/npc/huangrong.c
// Modified by action@sj
//���Ӣ�۴���28��

#include <ansi.h>
inherit NPC;
int say_lu1();
int say_lu2();

void create()
{
	set_name("����", ({ "huang rong", "huang", "rong" }));
	set("long",
			"���������䣬����ʮ��������ͣ�����ʤѩ�������ޱȣ���ɫ���������ɱ��ӡ�\n"
			"���������磬ȫ����£�ͷ��������һ���������Ȼ���⡣һ��װ��������Ůһ�㡣\n");
	set("gender", "Ů��");
	set("rank_info/rude", "С��Ů");
	set("title","ؤ�����");
	set("age",38);
	set("attitude","peaceful");
	set("str", 16);
	set("dex", 26);
	set("con", 28);
	set("int", 50);
	set("per", 50);
	set("shen_type", 0);

	set("tu", 1);
	set("shu", 1);
	set("shouhuan",1);

	set("jiali",200);
	set_skill("force", 500);
	set_skill("huntian-qigong", 500);
	set_skill("bihai-chaosheng", 500);
	set_skill("dodge", 500);
	set_skill("xiaoyaoyou", 500);
	set_skill("parry", 500);
	set_skill("strike", 500);
	set_skill("luoying-zhang", 500);

	set_skill("hand", 500);
	set_skill("lanhua-shou", 500);
	set_skill("finger", 500);
	set_skill("tanzhi-shentong", 500);
	set_skill("sword", 500);
	set_skill("yuxiao-jian", 500);
	set_skill("literate",500);
	set_skill("qimen-bagua", 500);
	set_skill("bangjue",200);
	set_skill("dagou-bang",500);
	set_skill("stick",500);

	map_skill("force", "huntian-qigong");
	map_skill("dodge", "xiaoyaoyou");
	map_skill("strike", "luoying-zhang");
	map_skill("hand", "lanhua-shou");
	map_skill("finger", "tanzhi-shentong");
	map_skill("parry", "dagou-bang");
	map_skill("sword", "yuxiao-jian");
	map_skill("stick", "dagou-bang");
	prepare_skill("hand", "lanhua-shou");

	set("chat_chance_combat", 100);
	set("chat_msg_combat", ({
		(: perform_action, "stick.chuo" :),
		(: perform_action, "stick.ban" :),
		(: perform_action, "stick.yin" :),
		(: perform_action, "stick.chuo" :),
		(: perform_action, "stick.chan" :),
		(: perform_action, "stick.wugou" :),
		(: exert_function, "huntian" :),
	}));

	set("combat_exp", 12500000);
	set("max_qi", 35000);
	set("max_jing", 14000);
	set("neili", 38500);
	set("max_jingli", 8500);
	set("eff_jingli", 8500);
	set("max_neili", 38500);

	set("inquiry", ([
	
		"����" : "�������Ȼ�е�ɵ�����ģ�����ȴ�����ĵġ�",	
	//	"�ܲ�ͨ" : (: ask_jiuyin :),
		"������" : "�ǵ��������Ե������ŵģ���ͬ�ķ����ʾس�ı仯���ÿ��سΪһ�ԣ����԰�˳���߶Ծ͹����ˡ�",
	/*	
		"���߹�" : (: ask_h7g :),
		"����ʮ����" : (: ask_xlz :),
		"�����" : (: ask_guojing :),
		"������β" : (: ask_slbw :),
		"�ֻ�" : (: ask_shouhuan :),
		"���" : (: ask_husband :),
		
// here add thd-job "ask huang" by Numa 19990911
		"ʦĸ": (: ask_job_s :),
		"��Ĺ": (: ask_job :),
// ask job times by Numa 19991005
		"����": (: ask_job_time :),
// add for taohua quest
		"÷����": (: ask_quest :),
		"������": (: ask_quest :),
// for hetu/luoshu
		"���Ű���": (: ask_book :),
		"��ǧ��": (: ask_qqzhang :),
		"��ǧ��": (: ask_qqchi :),
//		"��ǧ��": (: ask_qqren :),*/
	]) );

//here set do job's number
	set("thd/havejob",1);

	setup();

	carry_object("/d/city/obj/necklace.c")->wear();
	carry_object("/d/city/obj/goldring.c")->wear();
	carry_object("/clone/weapon/zhubang")->wield();
}

int say_lu1()
{
	command("say ³���ϣ���ؤ�����֮λ���ǲ�����Ȥ�ġ�\n");
	command("say ƽʱҲ���������ֹ������������վͰ���򹷰������������㡣\n");
	command("sigh");
	command("say �ҽ������Ӳ���̫�ã���Ҫ�ڼ���ϰ���úð���ؤ�����ϰ�á�Ҳ����ȴ�ҵ�һ׮���¡�\n");
	command("consider");
}

int say_lu2()
{
	command("say ��ؤ��򹷰�����ʽ�Ϳھ���϶��ɣ�ֻ����һ�������ܷ��ӳ�������");
	command("say ǰ�������Ѿ�����ʽ�������㣬����ϰ��Ҳ����ˡ�");
	command("say ��򹷰����а����������������������⡢ת�˾�������������ؤ��������\n");
	command("say ���ᡢ�顢�桢����ƣ��轫�������Ĵ�ֻ����Ӱ������Ӱ����ѧ�����Ե�����������ǧ�");
	command("say ʵ�˴򹷰����ľ��������������֡�ǰ�������Ѿ�����ʽ�������㣬����ϰ��Ҳ����ˡ� ");
	command("say �����Ҿͽ���򹷰��ھ��������㣬��Ҫ�����ˡ�\n");
}
