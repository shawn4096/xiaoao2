


string ask_rmdf()
{	
	int i,j,t;
	object me = this_player();

	if (!me->query_temp("rmdf/askku"))
    {
		command("say ����Ȼ��Ȼ�󳹴��򣬵����������������ɧ�ţ��ѵ�������ˣ�");
        return "�ߺߣ�\n";
	}
	
	if (time()-me->query("quest/sl/rmdf/shoudao/time")<86400)
    {
		command("say ������̫�ڿ��ˣ����ڽ������Ƕ�������֪��ô����");
        return "������\n";
	}

	i = 20;
	if(me->query("m-card-vip")) i =  18;
	if(me->query("y-card-vip")) i =  15;
	if(me->query("buyvip"))     i =  10;
	i=random(i);

	j=random(me->query("kar"));
	//t=random(me->query_skill("blade",1))/10;
	t=random(me->query("int"));
	command("say ������ʮ���������ǲ���֮�أ��ҵ�ʱ������ħ��������֪������Щ�ؼ���\n");
	command("say ����Ϊ�������Ѿ��ݺ����£��첻�ϵ�ʱ�Ѿ�����ħ����\n");
	command("say ����˶������ӽ���һ�����ϵ���ʹ������ħ���ڻ��⡣\n");
	command("say ��Ȼ�����ʦ������Ѱ�Ҵ��£�Ҳ�õ��˽����ž����ع����ֵ�ʱ���ˡ�\n");
	command("say ����ϸ�����ˣ��ܷ�����Ϳ�������ʺ�Ե���ˡ�\n");
	command("whisper "+me->query("id"));
	command("say �����������˹��������������������������ߣ�Ȼ��ۼ��ڴ��Ѩ....��\n");
	command("say ��������ô?��\n");

	command("pat "+me->query("id"));
	if( i<3 
		&& me->query("kar")<31
		&& t >= 40
		&& j > 26 ) 
	{
		tell_object(me,HIY"\n�������Ħ�ǵ�ָ�㣬��ȼľ��֮�ֵ������İ��������ĵá�\n"NOR);
		tell_object(me,HIG"\n����ͼ����Ϣ�嵽�͹�Ѩ�У�ͻȻֻ������������һ������ֱͨ˫�֣����Ͼ���������Ȼһ�ᡣ\n"
			             +"������ʶ��˳��һ�ӣ�һ���ƿ�������������һ��������ǿ���ĺܡ�\n"
						 +"����������������ȼľ��֮�ֵ��������������÷��š����д�ϲ֮�£�������ʽ���಻��������\n"
						 +"����ʽ������ʹ���ŵ�һ��ͨ��ʱ���Ǽ��ѣ��ζ�������ͨ��������Ϥ����������\n"
						 +"���֮�䣬�����Ͼ�����ͨ��������ȼľ��֮�ֵ�����������\n"NOR);
		me->set("quest/sl/rmdf/shoudao/pass",1);
		log_file("quest/rmdfshoudao", sprintf("%8s(%8s) ʧ��%d�κ�ѧ��ȼľ��֮�ֵ�����,�����ڻ��ͨ�������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��������ȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/sl/rmdf/shoudao/fail"),i,j,t,me->query("combat_exp")) );
		command("haha"+me->query("id"));
		me->set("title",HIY"������"+HIR"ȼľ��������"NOR);
		me->delete_temp("rmdf");
		return "��ϲ����ȼľ��֮�ֵ������ɹ�!\n";
		
	}	
   else
	{
		log_file("quest/rmdfshoudao", sprintf("%8s(%8s) ����ȼľ��֮�ֵ���������ʧ��%d�Σ��������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��������ȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/sl/rmdf/shoudao/fail"),i,j,t,me->query("combat_exp")) );
		
		tell_object(me,HIY"�������Ħ�ǵ�ָ�㣬���Ƕ�ȼľ��֮�ֵ������İ���ȫȻ����Ҫ�졣\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("quest/sl/rmdf/shoudao/fail",1);
		me->set("quest/sl/rmdf/shoudao/time",time());
		me->start_busy(1+random(3));
		me->delete_temp("rmdf");
		return "�ǳ��ź�����ȼľ��֮�ֵ�����ʧ��"+me->query("quest/sl/rmdf/shoudao/fail")+"�Ρ�\n";
	}
}


string ask_jiasha()
{
        object me=this_player() , armor;
        int i;

        if ((string)me->query("family/family_name") != "������")
                i = 5;
        else
                i = 1;

        if(me->query_temp("xs/xs_job") >= 1*i) {
                armor = present("shisan longxiang", this_object());
                if(!objectp(armor))     armor = unew(ARMOR_D("lx_cloth"));
                if(!objectp(armor))
                        return "ʮ�������������ڲ��������";  

                command("remove shisan longxiang");
                armor->move(me);
                command("emote ����һ��ʮ���������ġ�");
                command("wear jiasha");
                me->set_temp("xs/xs_job",0);
        }
        else
                return "�Ķ������ж����õ�ʵ�ʳɼ������ҿ��\n";

        return "�ã����ʮ��������������ȥ�ɣ�";
}