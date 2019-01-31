//ytx.c

inherit NPC;
#include <ansi.h>
int ask_jiuyuan();
#define QUESTDIR "quest/���Ӣ�۴�/"
#define QUESTDIR1 "quest/���Ӣ�۴�/��ѩ����/"

void greeting(object me);
string ask_hejiu();

void create()
{
	set_name("��Х��", ({ "guo xiaotian", "guo", "xiaotian" }) );
	set("gender", "����" );
	//set("title", "");
	set("nickname", "����֮��");
	set("age", 28);
	set("long",
"����Ŀ��࣬Ũü���ۡ�\n"
"������ɽ���ú����������ʹ��ʢ�ĺ����\n");
	set("str", 25);
	set("dex", 25);
	set("con", 25);
	set("int", 25);
	set("per", 25);
	set("shen_type", 1);
  set("no_get", 1);
  set("no_bark", 1);
	set_skill("force", 300);
	set_skill("dodge", 300);
	set_skill("parry", 300);
	set_skill("cuff",300); 
	set_skill("jinyan-gong",300);
	set_skill("taizu-quan",300);
	set_skill("xiantian-gong",300);
	map_skill("force","xiantian-gong");
	map_skill("cuff","taizu-quan");
	map_skill("dodge","jinyan-gong");
    prepare_skill("cuff", "taizu-quan");
    
	set("combat_exp", 4000000);
	set("max_qi", 20000);
	set("max_jing", 5000);
	set("max_neili", 15000);
	set("eff_jingli",4000);
	set("qi",20000);
	set("jing",5000);
	set("jingli",4000);
	set("neili", 15000);

  set("inquiry", ([
    "��Ԯ": (: ask_jiuyuan :),
	 "�Ⱦ�": (: ask_hejiu :),

		"������": "��������ܡ�",
    "��Ƽ" : "�����һ�ҡ�",
    "����" : "����һ�����˸���δ�����Ķ�Ůȡ�����֡�",
    "�" : "��������������ĵĹ��⡣",
    "��ϧ��" : "�����ҵ�ϱ��",

	]));
	set("chat_chance", 10);
        set("chat_msg", ({
		"���ﲻ��ô�ĳ��ִ���������⵽���Ƿ�����ʲô���顢����\n",
		"���Ӻ͵�ϱ��Ҫ���ˣ���ڹ�������ô�ᷢ�����������ء�����\n",
        }) );
     setup();
	carry_object("/clone/armor/cloth.c")->wear();
	carry_object(ARMOR_D("shoes"))->wear();
} 
string ask_hejiu()
{
	object me=this_player();
	if (me->query("shen")<0)
	{
		command("say ��һ��а������Ȼ�������ҺȾƣ���Ĳ��ͷ���ô��\n");
		return "�ߣ�\n";
	}
	if (me->query("combat_exp")<2000000)
	{
		command("say �㾭��ֵ����2m,�������ҺȾƣ��ѵ��������Լ�����Сô��\n");
		return "�ߣ�\n";
	}
	if (!me->query_temp(QUESTDIR1+"start"))
	{
		command("say ���޺þƣ���Ե�޹����ҺȾ��ѵ�����Ԥı��\n");
		return "�ߣ�\n";
	}
	command("say "+me->query("name")+"����Ȼ���ϵ����������ҺȾƣ��������ȥ�Ķ����Һ����ϵ�һ�ᵽ��\n");
	me->set_temp(QUESTDIR1+"askguo",1);
	return "�캮�ض����ȵ�ƿ���ů��ů�ͣ�\n";

}

int ask_jiuyuan()
{
	object me = this_player();
	if(!me->query(QUESTDIR1+"killsongbing"))
    {
	   command("sigh "+me->query("id"));
	   command("say ��λ"+RANK_D->query_respect(this_player())+"����������̫ƽ��Ҫ�������ٺ�һ�٣���\n");
	   return 1;
    } 

	if(me->query_temp(QUESTDIR1+"jiuyuan"))
    {
	   command("beg1 "+me->query("id"));
	   command("say ��λ"+RANK_D->query_respect(this_player())+"����ȥ������ܰ���Ҫ��������ס�ˣ�");
	   return 1;
    } 
	if(me->query(QUESTDIR1+"over"))
    {
	  command("beg1 "+me->query("id"));
	  command("say ��л��λ"+RANK_D->query_respect(this_player())+"���־������ѽ��");		
	  return 1;
    } 
    if( me->query("combat_exp") < 2000000 )
    {
	  command("disapp "+me->query("id"));
	  command("say ���㵱ǰ�ľ�����»����ܰ�æ��Ԯ����ܣ�����ץ��ȥ����ȥ�ɡ�\n");
      return 1;
    }  	
    if(me->query(QUESTDIR+"time") && time()-me->query(QUESTDIR+"time")<86400)
	{
	  command("shake "+me->query("id"));
	  command("say �����Ȱﵽ����ɣ�����ɡ�");
	  return 1;
    }
    if(!me->query(QUESTDIR1+"over"))
    {
	   me->set_temp(QUESTDIR1+"jiuyuan", 1);
	   me->set(QUESTDIR+"time",time());
	   me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
	   command("cry "+me->query("id"));
	   command("say �����Һ���ܾ�Ԯһλ�����׷ɱ�ĵ�ʿ��û�뵽����ȴ���н����ץ���ǣ�\n"+
				   "��λ������Ͽ�ȥ����ܼҽ������������İɣ���׼�����������͵���");
	   return 1;
    }
}

