// duan2.h
#include <ansi.h>
//#include TLS_QUEST_YYZ "";


string ask_helpwf()
{
    object me=this_player();
	//����ɽ�ҵ����������
	if (me->query_temp("yyzhi/helpyuxu"))
	{
		return "��л������������\n";
	}
	if (!me->query("quest/�����˲�/�书/yuxiang"))
	{
		return "������˵������ɽһ������֪���������Ƿ�ȫ���浣�������ˡ����������ȷ�һ�š�\n";
	}
	if (me->query("family/family_name")!="������")
	{
		return "�㲻���������µ�������������\n";
	}
	if (me->query_skill("force",1)<300)
	{
		return "��Ļ����ڹ�����300������Ҳ�ﲻ��æ��\n";
	}
	command("say ���մ����Ĵ���˿�ʼ�ڴ������Ű���Һܵ��������İ�ȫ��");
	command("consider ");
	command("say �������ľ�����ȥһ������ۣ���ס�ſڣ�ǧ�����������ܵ��˺���\n");
	command("say ���������������͡�\n");
	me->set_temp("yyzhi/first",1);
    tell_object(me,HIC"�������ڷ�����������ȥ�����������ƺ����ش�����Ҫ�����Ƶá�\n"NOR);
	return "��������̾һ����������ԩ��������\n";

}
//�ڶ�������Ҫ�ҵ��������⿪����ɽ����
string ask_helpmwq()
{
    object me=this_player();
	//����ɽ�ҵ����������
	if (me->query_temp("yyzhi/helpmuover"))
	{
		return "��л�����������\n";
	}
	if (!me->query_temp("yyzhi/helpyuxu"))
	{
		return "�����������������ã���̸ʲô����ľ���壿\n";
	}
	if (me->query("family/family_name")!="������")
	{
		return "�㲻���������µ�������������\n";
	}
	command("say ���մ����Ĵ���˿�ʼ����������һ��׷ɱľ���壬�Һܵ������İ�ȫ��\n");
	command("say ��˵���������Ĵ���ˣ�������������������ʿҲ�������У������ǵ��ġ�\n");
	command("say ����֮�¸п���ǧ�����������һ�������Ҷ�����.\n");
	command("sigh ");
	command("say �������İ���£�������ȥ�ʹ��һʺ�Ҫһ��Ҫ��Ʒ���������֮���һ����֪��\n");
	me->set_temp("yyzhi/findqueen",1);
	me->delete_temp("yyzhi/helpwf");
    tell_object(me,HIC"�������ڷ�����������ȥ�����������ƺ����ش�����Ҫ�����Ƶá�\n"NOR);
	return "�������ƺ���ɫ��Щ���Σ���ס���֡�\n";

}
//���������ȸʱ���
string ask_helpgbb()
{
    object me=this_player();
	if (me->query_temp("yyzhi/helpgbbover"))
	{
		return "��л�����˱�����\n";
	}
	if (!me->query_temp("yyzhi/helpmuover"))
	{
		return "����������������ã���̸ʲô�����ҵı�����\n";
	}
	command("say ���մ����Ĵ���˿�ʼ����в�ҵı������Һܵ������İ�ȫ��\n");
	command("say ����֮�¸п���ǧ���������Ƕ���֮��������ұ����ñ������Ҷ�����.\n");
	command("sigh ");
	command("say �������ľ�����ȥ����ٹ�ȥ�����ʺ����ҵı�����\n");
	me->set_temp("yyzhi/helpgbb",1);
	me->delete_temp("yyzhi/helpmuover");
    tell_object(me,HIC"�������ڷ�����������ȥ�����������ƺ����ش�����Ҫ�����Ƶá�\n"NOR);
	return "��������ɫ���Σ���ס���֡�\n";

}
//���Ĳ����Ȼ��غ���
string ask_helpqhm()
{
    object me=this_player();
	if (me->query_temp("yyzhi/helpqhmover"))
	{
		return "��л�������ҵ����ޡ�\n";
	}
	if (!me->query_temp("yyzhi/helpgbbover"))
	{
		return "�����ҵı������������ã���̸ʲô�����ҵ����ޣ�\n";
	}
	command("say ���մ����Ĵ���˿�ʼ����в�ҵ����ޣ��Һܵ������İ�ȫ��\n");
	command("say ����֮�¸п���ǧ���������Ƕ���֮��������ұ��������ޣ��Ҷ�����.\n");
	command("sigh ");
	command("say �������ľ�����ȥ����������ȥ�����ʺ����ҵ����ޡ�\n");
	me->set_temp("yyzhi/helpqhm",1);
	me->delete_temp("yyzhi/helpmuover");
    tell_object(me,HIC"�������ڷ�����������ȥ�����������ƺ����ش�����Ҫ�����Ƶá�\n"NOR);
	return "��������ɫ���Σ���ס���֡�\n";

}


//���岽 �黨�´�ս
string ask_helpnhs()
{
    object me=this_player();
	if (me->query_temp("yyzhi/helnhsmover"))
	{
		return "��л�����������黨�»�ü��ʦ��\n";
	}
	if (!me->query_temp("yyzhi/helpqhmover"))
	{
		return "�������޶��������ã���̸ʲô����ȥ���ˣ�\n";
	}
	command("say ������˵�Ĵ���˿�ʼ����в�Ҵ���Σ�������ҵ�����Ƕ��黨��һ�ˡ�\n");
	command("say ����֮�¸п���ǧ���������Ƕ���֮���������������ü��ʦ���Ҷ�����.\n");
	command("sigh ");
	command("say ���˻�ü��ʦ�ļ��룬�Ը��Ĵ���˾����������ˡ�\n");
	me->delete_temp("yyzhi");
	me->set_temp("yyzhi/helpnhs",1);
	
    tell_object(me,HIC"�������ڷ�����������ȥ�����������ƺ����ش�����Ҫ�����Ƶá�\n"NOR);
	return "�������������ء�\n";

}

/*

int accept_object(object who, object obj)
{
	
	//���к�
	if (who->query_temp("yyzhi/helpyuxu")&& obj->query("id")=="shouji"&&obj->query("name")=="���к׵��׼�")
	{
		who->delete_temp("yiyangzhi/helpyuxu");
		who->set_temp("yiyangzhi/duan2",1);
		tell_object(who,HIY"������������ö���к׵��׼����ƺ�����ĺøд�����\n"NOR);
        command("laugh ");
		obj->move(this_object());
		destruct(obj);
		message_vision(HIC"������˳�ִӿڴ����ͳ�һ���𶧸��㣬˵��������ȥ�Ⱦ�ȥ�ɡ�\n"NOR,who);
		who->add("combat_exp",random(2000));
		new("clone/money/gold")->move(this_object());
		message_vision(HIC"��ľ��������ˣ�\n"NOR,who);
		command("give 1 gold to "+who->query("id"));
		return 1;
	}
	
	//�Ϻ�����
	if (who->query_temp("yyzhi/helpmuover")&& obj->query("id")=="shouji"&&obj->query("name")=="�Ϻ�������׼�")
	{
		who->delete_temp("yyzhi/helpmuover");
		who->set_temp("yyzhi/send/over",1);
		write(HIY"������������ö�Ϻ�������׼��������������⣬�ƺ�����ĺøд�����\n"NOR);
        command("laugh ");
		obj->move(this_object());
		destruct(obj);
		message_vision(HIC"������˳�ִӿڴ����ͳ�һ���𶧸��㣬˵��������ȥ�Ⱦ�ȥ�ɡ�\n"NOR,who);
		who->add("combat_exp",random(2000));
		new("clone/money/gold")->move(this_object());
		message_vision(HIC"��ľ��������ˣ�\n"NOR,who);
		command("give 1 gold to "+who->query("id"));
		return 1;
	}
	//�����
	if (who->query_temp("yyzhi/three/ganover")&& obj->query("id")=="shouji"&&obj->query("name")=="�������׼�")
	{
		who->delete_temp("yyzhi/three/ganover");
		who->set_temp("yyzhi/three/over",1);
		write(HIY"������������ö�������׼��������������⣬�ƺ�����ĺøд�����\n"NOR);
        command("laugh ");
		obj->move(this_object());
		destruct(obj);
		message_vision(HIC"������˳�ִӿڴ����ͳ�һ���𶧸��㣬˵��������ȥ�Ⱦ�ȥ�ɡ�\n"NOR,who);
		who->add("combat_exp",random(2000));
		new("clone/money/gold")->move(this_object());
		message_vision(HIC"��ľ��������ˣ�\n"NOR,who);
		command("give 1 gold to "+who->query("id"));
		return 1;
	}
	//Ҷ����
	if (who->query_temp("yyzhi/four/askhuang")&& obj->query("id")=="shouji"&&obj->query("name")=="Ҷ������׼�")
	{
		who->delete_temp("yyzhi/four/askhuang");
		who->set_temp("yyzhi/four/over",1);
		write(HIY"������������öҶ������׼��������������⣬�ƺ�����ĺøд�����\n"NOR);
        command("laugh ");
		obj->move(this_object());
		destruct(obj);
		message_vision(HIC"������˳�ִӿڴ����ͳ�һ���𶧸��㣬˵��������ȥ�Ⱦ�ȥ�ɡ�\n"NOR,who);
		who->add("combat_exp",random(2000));
		new("clone/money/gold")->move(this_object());
		message_vision(HIC"��ľ��������ˣ�\n"NOR,who);
		command("give 1 gold to "+who->query("id"));
		return 1;
	}
	//������
	if (who->query_temp("yyzhi/five/..")&& obj->query("id")=="shouji"&&obj->query("name")=="Ҷ������׼�")
	{
		who->delete_temp("yyzhi/four/askhuang");
		who->set_temp("yyzhi/four/over",1);
		write(HIY"������������öҶ������׼��������������⣬�ƺ�����ĺøд�����\n"NOR);
        command("laugh ");
		obj->move(this_object());
		destruct(obj);
		message_vision(HIC"������˳�ִӿڴ����ͳ�һ���𶧸��㣬˵��������ȥ�Ⱦ�ȥ�ɡ�\n"NOR,who);
		who->add("combat_exp",random(2000));
		new("clone/money/gold")->move(this_object());
		message_vision(HIC"��ľ��������ˣ�\n"NOR,who);
		command("give 1 gold to "+who->query("id"));
		return 1;
	}



}*/