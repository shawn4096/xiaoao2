/*
int do_lingwu(string arg)
{
	object me=this_player();
	object who=this_object();
	int i = me->query_skill("douzhuan-xingyi", 1);
    int lv = me->query("max_pot")-100;
	if( !living(who))
		return notify_fail("Ľ�ݸ����ڵ�״���������޷��ش����κ����⡣\n");

	if ( me->query("family/family_name") != "����Ľ��")
		return notify_fail("�����Ľ�ݵ��ӣ������ֽ�ʲô����\n");

	if (!arg || arg !="douzhuan-xingyi" ){
		message_vision("$N��$n�ֽ�һЩ������ѧ�ϵ����ʡ�\n", me, who);
		command("dunno "+me->query("id"));
		return 1;
	}
	if (me->is_busy() || me->is_fighting()){
		command("say ����æ�Ÿɱ�������أ�æ������˵�ɡ�");
		return 1;
	}
	if( me->query("jing") < 10)
		return notify_fail("��̫���ˣ�������Ϣһ��ɡ�\n");
	if((int)me->query("potential", 1) < 1 )
		return notify_fail("��Ǳ�ܲ�����\n");
	if ( i <= 50 ){
		command("say ��Ķ�ת���Ƶȼ������������ܴ�������ѧ��ʲô��");
		return 1;
	}
	write("����Ľ�ݸ��ֽ̹��ڡ�" + to_chinese(arg) + "�������ʡ�\n");
	write(HIC"������Ľ�ݸ���ָ�㣬���򵽶�ת���Ƶľ������ڡ�\n");
	write(HIR"���[��ת����]��ߵ�����Ŀǰʵս�������Ƶ���߼���\n");
    me->set_skill("douzhuan-xingyi", lv);

       if (i >= lv -1)
         {
		command("say ���ʵս���鲻�����޷�����ʲô��");
		return 1;
	}
        
	return 1;
}*/
string ask_shixibiao()
{
	object me=this_player();
	if (!me->query("quest/�����˲�/��������ƪ/over"))
	{
		command("���Ȱ������˲����ܽ��꣬ʵ�����������ٸ����㡣\n");
		return "��͵����û�ţ�";
	}
	
	command("say �ðɣ���Ȼ����Ҿͽ�������¸����㡣\n");
	command("say ��Ȼ���Ѿ���Ľ��������ʵ�ĵ��ӣ�˵������Ҳ�޷���\n");
	command("say �Ҵ����ȷʵ�д���Ϯ��������Ϯ��ȴ��֪�����١�\n");
	command("say �������ģ��ҵ��ǿ���������һ�£�Ҳ�����Ե�ɺ������·���Ҳ˵������\n");
	command("say �������Ҹ���˵���������ҼҾټ���Ǩ֮�ʣ�����̫��һ������һ�����ˡ�\n");
	command("say ��ʱһ����ս��˫���������٣��������Ǵλ����У�װ��Ϯ����Ǹ����Ӳ������١�\n");
	command("say ����Ӧ�������䵽��һ����������˽�´������ǰ����˺��������ư���װ��Ϊ��\n");
	command("say ���Ժ��л���һ��������ǧ������һ���ˡ�\n");
	me->set_temp("sxb/askfu",1);
	return "��˼��㱣���֪������ʲô��ֻ�ǲ��ϵ��ֹ���ǰһ�׶ξ����ư���̽˵����\n���Ʒ�ʳָ���������˷��ֹ�һ����������֪�������Ǽ٣�\n";

}
string ask_mishi()
{
	object me=this_player();
	object key,wkey;
	if (!me->query("quest/�����˲�/��������ƪ/over"))
	{
		command("say ���Ȱ������˲����ܽ��꣬ʵ�����������ٸ����㡣\n");
		return "��͵����û�ţ�";
	}
	
	command("say �ðɣ��Ҵ������һ���������ң���������˴���������װ����\n");
	command("say ��Ȼ���Ѿ���Ľ��������ʵ�ĵ��ӣ�˵������Ҳ�޷���\n");
	command("say Ϊ�Ҵ����δ��������׼���ģ������ڸ���һ�ѽ�ȥ�ĺ�Կ�ף���ȥ���ҿ���\n");
	key=new("d/mr/obj/mrkey");
	key->move(me);
	command("say ��������һ�Ѱ�Կ�ף��ǳ���ʱ�����õģ�С���ղغ��ˡ�\n");
	wkey=new("d/mr/obj/mrkey1");
	wkey->move(me);
	return "���¶�Ҫ�����ģ���������սʤ��Ľ��ɽׯ���˻�û�����أ��úøɣ�\n";

}
