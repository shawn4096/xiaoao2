//tangfeng@SJ 2004
#include <ansi.h>
inherit NPC;
//inherit F_MASTER;

#define QUESTDIR1 "quest/�����˲�/�貨΢��ƪ/"
#define QUESTDIR2 "quest/�����˲�/����Ӫ��ƪ/"
#define QUESTDIR3 "quest/�����˲�/��������ƪ/"
#define QUESTDIR4 "quest/�����˲�/���ɾ�Ԯƪ/"

string askduanyu();
string tianlonghelp();
string asksave();
string askxiaofeng();
string askjiumozhi();
string huanggong();

void create()
{
        set_name("����ʯ", ({ "ba tianshi", "ba","tianshi" }));
        set("title", "�����˾��");
        set("gender", "����");
        set("age", 40);
        set("str", 28);
        set("dex", 20);
        set("long", "����ݺ�����Ȼ��ò��̣�ȴ�Ǹ�ʮ�־����ܸɵ���
���Ϊ����ʼ����²��ٹ��ͣ�Ŀ��λ��˾�ա�\n");
        set("max_qi", 5000);
        set("max_jing", 3000);
        set("neili", 5000);
        set("max_neili", 5000);        
        set("eff_jingli",3000);
        set("jiali",50);
        set("combat_exp", 1700000);
        set("shen_type", 1);
        set("attitude", "peaceful");
        create_family("������", 16 , "�׼ҵ���");
         
        set_skill("force",200);
        set_skill("whip",200);
        set_skill("cuff",200);
        set_skill("duanjia-quan",200);
        set_skill("dodge",200);
        set_skill("tianlong-xiang",200);
        set_skill("parry",200);
        set_skill("qiantian-yiyang",200);
        set_skill("qingxu-bian",200);
        map_skill("parry", "xiuluo-dao");
        map_skill("dodge", "tianlong-xiang");
        map_skill("cuff","duanjia-quan");
        map_skill("force", "qiantian-yiyang");
        map_skill("whip", "qingxu-bian");
        prepare_skill("cuff","duanjia-quan");
		set("inquiry",([
			"����" : (: askduanyu :),
			"����" : "������Ǵ���",
			"������" : "���������Ҷμ���ѧ�����֮�ء�",
			"��������" : (: tianlonghelp :),
			"Ӫ��" : (: asksave :),
			"���" : (: asksave :),
			"����" : "�����˳���Ľ�ݡ������壬�˵�һ���ú���",
			"Ӫ�ȶ���" : (: asksave :),
			"Ӫ������" : (: askxiaofeng :),
			"Ľ�ݸ�" : "�����˳���Ľ�ݡ������壬��˵Ľ�ݹ����꼶���ᣬȴ����������",
			"Ľ�ݲ�" : "����˵�ǣ�����Ľ�ݲ����Ľܲţ���ϧӢ�����š�",
			"�Ħ��" : (: askjiumozhi :),
			"������" : "��˵������������߾�ѧ���ҹ����Ⱳ��Ҳδ�ܼ�����",
		]));
	     set_temp("apply/attack", 70);
        set_temp("apply/defense", 70);
        set_temp("apply/armor", 70);
        set_temp("apply/damage", 20);        
        
        setup();
        carry_object("/clone/weapon/blade")->wield();
        carry_object("/d/dali/npc/obj/zipao")->wear();
}
/*
void attempt_apprentice(object ob)
{
	object me  = this_object();
	mapping fam = ob->query("family");
	if (ob->query("gender") == "Ů��"){
		command ("say ��λС�������������Ůͽ���㻹����ذɡ�");
		return;
	}
	if (ob->query("tls") && fam["family_name"]=="������" ){
		command ("say ���Ѿ��������³��ҵ����ˣ��Ҳ����������ˣ�");
		return;
	}
	if(ob->query("int") < 25){
		command("say ѧ�Ҵ���μ��书������ߣ����ҿ�" + RANK_D->query_respect(ob) + "�����Բ���25�������ƺ�������ϰ��");
		return;
	}
	if ((int)ob->query("shen") < 10000){
		command ("say  �Ҵ���������������ɣ����ҿ�" + RANK_D->query_respect(ob) +"������10k�����ʺ����Ҵ�����ϡ�");
		return;
	}
	if ( fam && fam["master_name"] == "������"){
		command("shake");
		command("say "+RANK_D->query_respect(ob)+"�Ѱ�������Ϊʦ��"+RANK_D->query_self(me)+"����������Ϊͽ��");
		return;
	}
	if( fam && fam["master_name"] == "������"){
		command("haha");
		command("say "+RANK_D->query_respect(ob)+"���ǻ�����ǰ��������"+RANK_D->query_self(me)+"����������Ϊͽ��");
		return;
	}
    if( fam && fam["family_name"!="������"] ){
		command("sigh ");
		command("say "+RANK_D->query_respect(ob)+"�㲻�����������׼ҵ��ӣ�����������Ϊͽ��");
		return;
	}
    if( (int)me->query("family/generation")<15){
		command("sigh ");
		command("say "+RANK_D->query_respect(ob)+"���Ѿ���ǰ����ʦ�̵�������������Ϊͽ��");
		return;
	}
	command("smile");
	command("say �ܺã�" + RANK_D->query_respect(ob) + "ֻҪ��Ϊ�Ҵ�������£����ձض��������ɾ͡�\n");
	command("say ��ϧ�����ү��������Ҫ�����飬��Ͼ��ͽ���㻹��ȥ�Ҵ�˾ͽ�ʹ�˾���������Ƿ���ʱ�䣿\n");
	//command("recruit " + ob->query("id") );
	//ob->set("title","��������������Ҷ�");
	return;
}

*/

string askjiumozhi()
{
	object me;
	me = this_player();
	if (me->query(QUESTDIR1+"over") && !me->query(QUESTDIR2+"start"))
	{
  	  command("nod "+me->query("id"));
		  return "��˵�������µ�һ��ɮ�Ħ�ǽ����������·𷨽����������Ҵ���֮�Ұ���";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh");
  	  command("? "+me->query("id"));
		  return "��ħɮ��Ȼ����۸��Ҵ������ˣ�ʲô��ެ����һ�𷨸�ɮ����P��P��";
  }
	if (me->query(QUESTDIR2+"start")&& me->query(QUESTDIR2+"over"))
	{
  	  command("nod "+me->query("id"));
		  return "�Ħ����Ϊ�����һ�𷨸�ɮ����ν����������ȫ��һ�ɺ��ԡ�";
  }
  command("nod");
	return "���������Ħ������ެ���Ļ�������������˵���ߴ��ǻۣ���ͨ�𷨣������书Ҳ�Ǿ��ˡ�";
}
string askxiaofeng()
{
	object me;
	me = this_player();
  if(!me->query(QUESTDIR3+"start"))
  {
  	  command("hoho");
  		return "�����˳���Ľ�ݡ������壬�˵�һ���ú�������Ԯ��֮˵��";
  }
	if (me->query(QUESTDIR3+"start") && !me->query(QUESTDIR3+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "��˵������飬ֻ���漰�����������֮������֪��������ô����";
  }

	if (me->query(QUESTDIR3+"bad"))
	{
  	  command("heng");
  	  command("? "+me->query("id"));
                  return "���壬�Ѳ��������ȳ���ԭ��������ν��Ȳ�֪ʲô��˼�������ʣ�";
  }
	if (me->query(QUESTDIR3+"start") && me->query(QUESTDIR3+"over")&& !me->query(QUESTDIR4+"start"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "��˵������飬ֻ���漰�����������֮������֪��������ô����";
  }
	if (me->query(QUESTDIR4+"start")&& !me->query(QUESTDIR4+"over"))
	{
  	  command("nod "+me->query("id"));
		  return "��������С���ӵ����֣���ȻҪ�ȡ���λ"+RANK_D->query_respect(me) +"������һ��������Һ��Ҽ�С����һ��Ԯ����";
  }
	if (me->query(QUESTDIR4+"start") && me->query(QUESTDIR4+"over"))
	{
  	  command("haha "+me->query("id"));
		  return "��һս����ʹ�죬"+me->query("name")+"�����������֣��˵���������";
  }
  command("hoho");
	return "�����˳���Ľ�ݡ������壬�˵�һ���ú�������Ԯ��֮˵��";
}
string asksave()
{
	object me;
	me = this_player();
  if(!me->query(QUESTDIR1+"start") &&!me->query(QUESTDIR2+"start"))
  {
  	  command("hoho");
  		return "С����������ϲ��ѧ��ֻ�����׾���ƽ�׽��ˣ�����Ԯ��֮˵��";
  }
	if (me->query(QUESTDIR1+"start") && !me->query(QUESTDIR1+"wuliangover")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "��˵��ǰ��ʱ��С���Ӻ����������ǳ���һ��������δ�лؼң���֪"+RANK_D->query_respect(me) +"�ɷ��������һ�¡�";
  }
	if (me->query(QUESTDIR1+"start") && me->query_temp(QUESTDIR1+"yingjiu")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "��֪���ˣ������Ͼ�ȥ��һ����ϻ����ޡ�";
  }
	if (me->query(QUESTDIR1+"start") && me->query(QUESTDIR1+"over")&& !me->query(QUESTDIR2+"start"))
	{
  	  command("thank "+me->query("id"));
		  return "��л"+RANK_D->query_respect(me) +"���С���ӣ�ֻ���Դ���ٹȻ�����С���Ӿ����㱣���֪���кζ������ܺ������ˡ�";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over")&& !me->query_temp(QUESTDIR2+"caught"))
	{
  	  command("sigh "+me->query("id"));
		  return "С��������ٹȻ�����������Ѫ�������������죬�ű������������ȥ�ˡ�";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh "+me->query("id"));
		  return "��Ȼ�ǳ��Ħ����ȸ��֣���Ը���Ӽ������డ��";
  }
  command("hoho");
	return "С����������ϲ��ѧ��ֻ�����׾���ƽ�׽��ˣ�����Ԯ��֮˵��";
}
string askduanyu()
{
	object me;
	me = this_player();
  if(!me->query(QUESTDIR1+"start" )&&!me->query(QUESTDIR2+"start"))
  {
  	  command("hoho");
  		return "С����������ϲ��ѧ��ֻ�����׾���";
  }
	if (me->query(QUESTDIR1+"start") && !me->query(QUESTDIR1+"wuliangover")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "��˵��ǰ��ʱ��С���Ӻ����������ǳ���һ��������δ�лؼҡ�";
  }
	if (me->query(QUESTDIR1+"start") && me->query_temp(QUESTDIR1+"yingjiu")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "����̽����С���ӱ���ٹ�����������ٹ�ʲô�ط�����";
  }
	if (me->query(QUESTDIR1+"start") && me->query(QUESTDIR1+"over")&& !me->query(QUESTDIR2+"start"))
	{
  	  command("thank "+me->query("id"));
		  return "��л"+RANK_D->query_respect(me) +"����Ҽ�С���ӡ�";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over")&& !me->query_temp(QUESTDIR2+"caught"))
	{
  	  command("sigh "+me->query("id"));
		  return "С��������ٹȻ�����������Ѫ�������������죬�ű������������ȥ�ˡ�";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh "+me->query("id"));
		  return "��Ȼ�ǳ��Ħ����ȸ��֣���Ը���Ӽ������డ��";
  }
  command("hoho");
	return "��������������֮�ӡ�";
}
string tianlonghelp()
{
	object me;
	me = this_player();
  if(!me->query(QUESTDIR1+"over"))
  {
  	  command("haha");
  		return "���������Ҷμ���ѧ�����֮�أ��������ƣ��벻ҪΣ��������";
  }
	if (me->query(QUESTDIR1+"over") && !me->query(QUESTDIR2+"start"))
	{
  	  command("nod "+me->query("id"));
		  return "��˵�������¸�ɮ�Ħ�ǲ��ս����������£���֪��ϲ�ǻ���";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh");
		  return "��ħɮ��Ȼ����۸��Ҵ������ˣ�ʲô��ެ����һ�𷨸�ɮ����P��";
  }
	if (me->query(QUESTDIR2+"over"))
	{
  	  command("thank "+me->query("id"));
		  return "��л"+RANK_D->query_respect(me) +"�����ⳡ����Σ���������Ҵ���С���ӵ��Խ�ȡ�";
  }
  command("hoho");
	return "���������Ҷμ���ѧ�����֮�أ��������ƣ��벻ҪΣ��������";
}
