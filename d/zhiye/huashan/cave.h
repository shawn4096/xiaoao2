string *ssjf_yanlian = ({
HIC"��ʹһ�С��������ڡ�����һ����ʽ����ʱ����һƬ����ָ���Ե���ǰ����"NOR,
HIG"��ʹһ�С����ż�ɽ�����������ߣ���ָ���϶��»���һ���󻡣���ǰ��������ȥ��"NOR,
HIW"����ǰ����һ������ָ�������ƼȻ�����������������ȴͻȻָ��һת��ʹ����������ɽ��ֱ��ǰ��!"NOR,
HIR"����ָһ����һʽ��ǧ����������������Ϣ�ػ���ǰ��!"NOR,
HIY"��һʽ������������������Ʈ�����ߣ��˷���������ָңҡָ��ǰ����"NOR,
HIM"�����ǰ��ʹ��������ء��������������ޣ���ָ�����ػ���ǰ����"NOR,
WHT"����Ƶ�����һʽ�����両�ࡹ����ָ�Ի���Ծ�����缲�������ǰ����"NOR,
HIB"�㽣ָ΢����������һ�С���Х���졹���йǽ�����쫷�����ǰ����"NOR,
YEL"�㽣ָ������仯������һ�С���������������������֮���£������޶�������׽����"NOR,
RED"��ͻȻ��������б��ܳ���ʹ�������ף�ڡ���ƾ�����������Ƴ�������������ʱ֮������ǰ���ռ䡣"NOR,
CYN"�����ִ�������ס�ζ�����ʯ��������ʹ�����������������������޷��жϳ��˶����С�"NOR,
MAG"�㽣�й��Ƽ�ǿ��ȴȫ�����Է�������·��ʹ��һ�С������ϸǡ����仯Ī��ع���ǰ�������ƾ���˿�������Ѱ��"NOR,
});
string *tmgf_yanlian = ({
HIC"��ʹһ�С��ºڷ�ߡ�����һ����ʽ����ʱ����һƬ����ָ���Ե���ǰ����"NOR,
HIG"��ʹһ�С���糤�š����������ߣ���ָ���϶��»���һ���󻡣���ǰ��������ȥ��"NOR,
HIW"����ǰ����һ������ָ�������ƼȻ�����������������ȴͻȻָ��һת��ʹ�������·ת��ֱ��ǰ��!"NOR,
HIR"����ָһ����һʽ���������⡹��������Ϣ�ػ���ǰ��!"NOR,
HIY"��һʽ���������桹������Ʈ�����ߣ��˷���������ָңҡָ��ǰ����"NOR,
HIM"�����ǰ��ʹ�������R�L�����������������ޣ���ָ�����ػ���ǰ����"NOR,
WHT"����Ƶ�����һʽ����Գ�ݷ𡹣������Ի���Ծ�����缲�������ǰ����"NOR,
HIB"�㳤��΢����������һ�С���Գ���ҡ��������Ӱ��쫷�����ǰ����"NOR,
});

int ssjf_zhuomo(object);

int ssjf_zhuomo(object me)
{
    if((int)me->query("ssjf/jueji/fail")>=5 && me->query("registered")<3)
    {
         write("������Ⱳ�Ӷ��޷���ĥ͸��������ˡ�\n");
         return 1;
     }

    if((int)me->query("ssjf/jueji/time")+86400>time())
    {
         write("�����ĥ��������Ŀǰ���޷�������չ��\n");
         return 1;
     }

    if((int)me->query("ssjf/jueji/exp")+50000>(int)me->query("combat_exp"))
    {
         write("����۵�ʵս�����л�����!\n");
         return 1;
     }

    if(me->query("ssjf/jueji/yanlian")=="pass")
    {
         write("����������Լ���ˮƽ��ʵ���޷���ĥ�����Ľ��У�\n");
         return 1;
     }

    write(HIG"������۾���������ĥ����ɽ������ÿһ�У�ÿһʽ��������������ǰ������\n\n"+
          HIY"��˼�������������Ϊ�����Ȼ�����������ʱ���Ѹ������ں�ʹ������ʽ��\n"+
          HIY"��������ʹ����\n"NOR);

    me->start_busy(999);//��ֹplayer���߶�. by lsxk@hsbbs
    call_out("ssjf_yanlian",3,me);
    return 1;
}

int ssjf_yanlian(object me)
{
    int i;
    string killer_location;
    if(file_name(environment(me))!="/d/huashan/cave"
      &&file_name(environment(me))!="/u/lsxk/partyskill/newhs/quest/cave")
         return 1;

    if((int)me->query_temp("ssjf/jueji/yanlian")>7){
        if(!random(4)||me->query("ssjf/jueji/yanlian")=="again"){
          write(HIC"\n�����о��ް�������������ʹ��һ���ǳɣ������νӵ������޷죬������\n"+
                     "ȱ��������ȴ���ɾ����޷������������ںϣ��κ�һ�ж���������\n"+
                     "��׸֮�С���ֻ���ã����޸���ָ�㣬�������Է�������ɽ������\n"+
                     "����������\n"NOR);
            me->delete_temp("ssjf_zhuomo");
            me->delete_temp("ssjf/jueji/yanlian");
            //me->set("ssjf/jueji/meet_killers",1);
            me->set("ssjf/jueji/yanlian","pass");
            me->set("ssjf/jueji/yanlian_time",time());
            me->set("ssjf/jueji/yanlian_exp",me->query("combat_exp"));
/*
            i = random(4);
            switch(i)
            {
                 case 0 : killer_location="qlmnj";break;
                 case 1 : killer_location="zqmnj";break;
                 case 2 : killer_location="xwmnj";break;
                 default : killer_location="bhmnj";break;
             }*/
            me->start_busy(1);
            me->set("ssjf/jueji/location",killer_location);
            log_file("quest/ssjueji", sprintf("��ɽ������¼��%s(%s)�ڻ�ɽ�ض���ĥ������ɽ�ؼ��ɹ�������%d��", me->name(1),me->query("id"), me->query("combat_exp")) );
            return 1;
        }
        else{
            write(HIR"������ƺ��е��ĵã����ܻ���ҪһЩʵս�����۾���ɡ�\n"NOR);
            me->delete_temp("ssjf_zhuomo");
            me->delete_temp("ssjf/jueji/yanlian");
            me->set("ssjf/jueji/yanlian","failed");
            me->set("ssjf/jueji/yanlian_time",time());
            me->set("ssjf/jueji/yanlian_exp",me->query("combat_exp"));
            me->start_busy(1);
            log_file("quest/ssjueji", sprintf("��ɽ������¼��%s(%s)�ڻ�ɽ�ض���ĥ������ɽ�ؼ�ʧ�ܡ�����%d��", me->name(1),me->query("id"), me->query("combat_exp")) );
            return 1;
        }
    }
    else{
        me->add_temp("ssjf/jueji/yanlian",1);
        call_out("ssjf_yanlian",5,me);
        return 1;
    }

    return 1;
}
