// sha.c ��ɽ�ɵ��������� ɳ�콭
// Creat by Lklv 2001.10.18

#include <ansi.h>
inherit NPC;
string ask_pixie();
string ask_job();
int ask_fangqi();
inherit F_MASTER;

void create()
{
        set_name("ɳ�콭", ({ "sha tianjiang", "sha", "tianjiang" }));
        set("nickname", WHT"ͺӥ"NOR);
        set("long", "����һ��ͺͷ����,�Ͳ����ǳ��ڻ켣�ڽ��ӵ�Ӣ����\n");
        set("gender", "����");
        set("unique", 1);
        set("age", 45);
        set("per", 20);
        set("attitude", "heroism");
        set("shen_type", -1);
        set("str", 26);
        set("int", 26);
        set("con", 26);
        set("dex", 27);
        set("unique", 1);

        set("max_qi", 13000);
        set("max_jing", 4000);
        set("eff_jingli", 4000);
        set("jiali", 150);
        set("combat_exp", 3600000);
        set("eff_neili", 4000);
        set("shen", -150000);
		set_skill("songyang-jue", 150);

		set_skill("literate", 100);
		set_skill("force", 250);
		set_skill("parry", 250);
		set_skill("blade", 250);
		set_skill("dodge", 250);
		set_skill("hand", 250);
		set_skill("zhongyuefeng", 250);
		set_skill("songyang-shou", 250);
		set_skill("hanbing-zhenqi", 250);
		set_skill("fenshui-daofa", 250);
		//set_skill("whip", 220);
	  //  set_skill("songyang-bian", 220);

		map_skill("force", "hanbing-zhenqi");
		map_skill("dodge", "zhongyuefeng");
		map_skill("hand", "songyang-shou");
		map_skill("parry", "songshan-jian");
		map_skill("blade", "fenshui-daofa");
		prepare_skill("hand", "songyang-shou");

		create_family("��ɽ��", 4, "����");
		set("class", "songshan");
		set("chat_chance_combat", 10);
		set("chat_msg_combat", ({
			(: perform_action, "blade.fenshui" :),
			(: perform_action, "hand.junji" :),
			(: exert_function, "juhan" :),
		}));
		set("inquiry", ([
			"��а����" : (: ask_pixie :),
			"����" : (: ask_job :),
			"����" : (: ask_fangqi :),

		]) );
			setup();
			carry_object(ARMOR_D("changpao1"))->wear();
			carry_object(BINGQI_D("blade"))->wield();
}
void attempt_apprentice(object ob)
{
	if (!ob->query("quest/ss/rumen/pass"))
	{
		command("say ����ͨ������ʦ�ܵĿ�����˵��\n");
		command("say ���кεº��ܰ���Ϊʦ��\n");
		command("say ���ֺ�ԭ�ι�����Ϊͽ��\n");
		command("say ����ɽ��Ҫ�ҳϵ���ͽ���㻹���������ҿ��ɣ�\n");
		return;
	}
	if (ob->query("family/family_name")!="��ɽ��")
	{
		command("say һ�����ǹ������֮ͽ��Ϊ�ε��ˣ�\n");
		return;
	}
	if(ob->query_skill("hanbing-zhenqi",1) < 120 ){
		command("say ��ĺ�������̫���ˣ�����120�������ң�");
		return;
	}
	if(ob->query("party/gongji") < 1000 ){
		command("say ������ɹ�������1000���������ң�");
		return;
	}
	if(ob->query("shen") > -10000 ){
		command("say ��ɽ�����Ժ������ƣ�<-100k������������ǻһ���Ͳ����ĺ������������");
		return;
	}
	command("say �ðɣ�ʦ����Ҫ�Ҷ�����һЩ������������ɽ���ء�");
	command("recruit " + ob->query("id"));
}

string *names = ({
"/d/fuzhou/bank",	"/d/fuzhou/beijie",	"/d/fuzhou/beimen",
"/d/fuzhou/biaoju",	"/d/fuzhou/bridge",	"/d/fuzhou/chalou",
"/d/fuzhou/chalou2",	"/d/fuzhou/dangpu",	"/d/fuzhou/dongjie",
"/d/fuzhou/dongxiang","/d/fuzhou/dongxiang2",
"/d/fuzhou/feiyuan",	"/d/fuzhou/fenduo1",	"/d/fuzhou/haigang",
"/d/fuzhou/houyuan",		"/d/fuzhou/huadian",	"/d/fuzhou/island1",
"/d/fuzhou/island2",	"/d/fuzhou/island3",	"/d/fuzhou/island4",
"/d/fuzhou/island5",	"/d/fuzhou/jiuguan",	"/d/fuzhou/kezhan",
"/d/fuzhou/kezhan2",	"/d/fuzhou/lagoon",	"/d/fuzhou/lagoon1",
"/d/fuzhou/lagoon2",	"/d/fuzhou/laozhai",
"/d/fuzhou/midao",	"/d/fuzhou/minzhai",
"/d/fuzhou/mupeng",	"/d/fuzhou/nanjie",	"/d/fuzhou/nanmen",
"/d/fuzhou/road1",	"/d/fuzhou/road2","/d/fuzhou/road3",
"/d/fuzhou/road4",	"/d/fuzhou/road5",	"/d/fuzhou/rock",
"/d/fuzhou/wroad1",	"/d/fuzhou/wroad2","/d/fuzhou/wroad3",
"/d/fuzhou/wroad4",	"/d/fuzhou/wroad5",	"/d/fuzhou/wroad6",
"/d/fuzhou/wroad7",	"/d/fuzhou/wroad8","/d/fuzhou/wroad9",
"/d/fuzhou/wroad10",	"/d/fuzhou/xijie",	"/d/fuzhou/xijie2",
"/d/fuzhou/ximen",	"/d/fuzhou/xixiang","/d/fuzhou/xixiang3",
"/d/fuzhou/xixiang4",	"/d/fuzhou/xixiang2",	"/d/fuzhou/xyxiang",
"/d/fuzhou/xyxiang2",	"/d/fuzhou/yaopu","/d/fuzhou/yuchuan1",
"/d/fuzhou/yuchuan2",	"/d/fuzhou/yuchuan3",	"/d/fuzhou/yuchuan4",
"/d/fuzhou/yuchuan5",	"/d/fuzhou/yugang",	"/d/fuzhou/zahuopu",
"/d/fuzhou/zhangfang",	"/d/fuzhou/zhengting","/d/fuzhou/zhongxin",
"/d/fuzhou/shanpo",	"/d/fuzhou/shiqiao","/d/fuzhou/wjiuguan"
});

string ask_pixie()
{
	object me=this_player();
	if (me->query("family/family_name")!="��ɽ��")
	{
		command("say �㲻������ɽ���ӣ�����������");
		return "�ߣ�";
	}
	if (me->query_skill("force",1)<100)
	{
		command("say ������ڹ�����100������������");
		return "�ߣ�";
	}
	
	command("say ��а�����Ǹ��ö�����\n");
	command("say ������Զͼƾ��ý������𽭺����޿�ƥ�С�\n");
	command("say ǰ�����������ڲ���Ϣ˵��ɽ����Ⱥ���α���Ӵ�����������֪������Ҫ��ʲô��\n");
	me->set_temp("ss/pixie/asksha",1);
	return "";

}


//������ɽ����а����job

string ask_job()
{
	object ob, me, ling;
	object jianxi;
	mixed objwhere;
	int i;
	string str,stw;
	me=this_player();
	ob = this_object();
	
	//ling = present("songyang ling", me);
    
	if (!me->query_temp("ss/pixie/asksha"))
	{
		command("say ������Ե�޹ʣ�ƾʲôҪ�ش�\n");
		return "�������Щ����ɵ��ˣ����м�ϸ��\n";
	}
	if(me->query("family/family_name")!="��ɽ��") 
           return "�㲻������ɽ���ӣ��������ɶ�Թ��Ͳ�Ҫ�����ˡ� ";

	if (me->query_temp("ss/pixie/name"))
		return "�Ҳ�������ȥ����һ��Ѱ�һ�ɽ�������Ǹ�͵�˱�а���׵�"+me->query_temp("ss/pixie/name")+"ô����\n";

	if ((int)me->query("combat_exp") < 100000)
		return "���书δ�ɣ���ôΣ�յ������Ǳ����ˣ�\n";

	if (me->query("job_name") == "��ɽ����а����")
		return "���������ɽ����а�����������Լ�ȥ��ϰ�书ȥ�ɣ�";

	if(me->query_condition("job_busy"))
		return "��������æ�������������أ�";
	if(me->query_condition("sspixie_busy"))
		return "��������æ������ɽ����а���������أ�";

	if(me->query_temp("quest/busy")) //added by tangfeng ��quest��ͻ
		return "����������û�и���������㻹���ȴ����������������˵�ɡ�";
    
	//�����ϸ����
    jianxi=new("/d/songshan/npc/hsdizi");
	jianxi->set("long",jianxi->query("long")+"\n����"+me->query("name")+"����׷ɱ�Ļ�ɽ�ɵ��ҷ��ӣ�\n"NOR);
	jianxi->set("owner",me->query("id"));
	//��ֵjianxi
	i=1;
	jianxi->do_copy(me,i);
	//�����ϸλ��
	//str=names[random(sizeof(names))];
	
	objwhere = names[random(sizeof(names))];

	//objwhere =load_object(str);
	if (!objwhere) objwhere = names[random(sizeof(names))];
	jianxi->apply_condition("npc_die",30);
	jianxi->move(objwhere);
	
	command("nod "+me->query("id"));
	message_vision(HIY"$N�������ã������߱��棬������ֻ�ɽ��α��������Ⱥ���µ������쳣���\n"NOR,me);
	tell_object(me,"�յõ��������е����鱨��ȷ���ǻ�ɽ�ɵ�����"+objwhere->query("short")+"��Բ�������������ּұ�а���ף�\n");
	tell_object(me,"���˵����ֽС�"+jianxi->query("name")+"("+jianxi->query("id")+")��������ȥ���أ�������Ŀ�ĵóѣ�\n");
	tell_object(me,"��������ʱ�������ձ����ֲ���ã�Ӧ�þ��ڸ���һ�����������ȥ��أ���Ҫ���飡\n");
	tell_object(me,"ץ������ֱ�Ӿ͵ش���������ͷ���ң�����Ч�ȣ�����������й��ڱ�а��������ϢҲһ�������ң�\n");
	
	me->set_temp("ss/pixie/place",objwhere->query("short"));
	me->set_temp("ss/pixie/id",jianxi->query("id"));
	me->set_temp("ss/pixie/name",jianxi->query("name"));
	me->set_temp("ss/pixie/time",time());
	me->set_temp("ss/pixie/nandu",i);
	
	me->apply_condition("sspixie_busy", 30 + random(5));
	me->apply_condition("job_busy", 30);

	
	return "���¹�ϵ�����Ų��ɴ��£��²����ɣ���Ҫ��ȥ��أ�\n";
	
}
int accept_object(object who,object obj)
{
	object obb;
	int gg;
	string msg;
	gg=1+random(3);
	obb=obj->query("kill_by");
	if (obj->query("name")==who->query("ss/pixie/name")
		||obb->query("id")==who->query("id"))
	{
		command("haha "+who->query("id"));
		command("say ���ܽ�"+obj->query("victim_name")+"���Сα���Ӹ���ɱ�ˣ��Һܸ��ˣ�\n");
		command("pat "+who->query("id"));
		command("say ��˵��������书���������Һܿ����㣡\n");
		command("say ������ȥ�ú���Ϣ�ɣ�\n");
		destruct(obj);
		message_vision(RED"\n\nɳ�콭˦�ֽ������ͷ��ʯ�������������ŵ�������ٺ���Ц���ѣ�\n"NOR,who);
	
	
		

		TASKREWARD_D->get_reward(who,"��ɽ��а",-1,0,0,2,0,0,0,"ɳ�콭");  
		who->add("party/gongji",1+random(1));
		//who->add("job_time/��ɽ׷ɱ",1);
		tell_object(who,HIG"������"+chinese_number(gg)+"�����ɹ��׽�����\n"NOR);
		who->set("job_name","��ɽ����а����");

		if (random(who->query("job_time/��ɽ��а"))>800
			&&random(who->query("kar"))>26)
		{
			message_vision(HIG"\nɳ�콭���������Ц��˵��������������޲����������Ҹ�������ٵس�Ϊ���ɵմ����ӡ���\n"NOR,who);
			who->set("title","��ɽ�ɵմ�����");
			who->set("quest/ss/dichuan",1);
		}
		//�����ж�ȥ���ܱ�а��������ʾ
		who->apply_condition("job_busy",3);
		who->apply_condition("sspixie_busy",3);
		who->delete_temp("ss/pixie");
	}	
	return 1;
}
int ask_fangqi()
{
	object me;
	mapping ob;
	string name;
	me=this_player();
	command("heng "+me->query("id"));
	command("angry "+me->query("id"));
	if (!me->query_temp("ss/pixie"))
	{
		command("say ��ʲô��û����Ϲ����ʲô��\n");
		return 1;
	}

	command("say ��Ȼ���겻�ɾ���ʱ��ȥЪϢȥ�ˣ������Ǽ�ס���ˡ�\n");
	me->delete_temp("ss/pixie");
	me->apply_condtion("job_busy",4);

	return 1;
}