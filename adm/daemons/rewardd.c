// ͳһ����������������by lsxk  2008/1/7
// By Spiderii@ty �Ӹ�������ϴ�ֵ�JOB�����Ȳ�ϴ�ֵĽ���һЩ
// update by lsxk@hsbbs 2008/3/17   ����ת�����exp�����ӳɣ�
// By Spiderii@ty ת�����pot���޵����ơ����̼����ת��
// Update By lsxk@hsbbs 2008/06/20  �����Խ�ɽׯ̽��������
// update by lsxk@hsbbs 2008/06/27 ���ת�����Ǳ�������޶�
// Update by Jpei@feixue �ſ�hardquo���޸�������


/* ����˵����
    obj:    �������
    job:    ��������
    shenflag:    �������־,����Ϊ1������Ϊ-1����������Ϊ0.
    potflag:    Ǳ�ܱ�־������1��Ǳ�ܳ����޸������򲻳����ޡ�
    credit:    ͨ����־��0Ϊ��ͨ��������-1Ϊ��ϵͳ���ݾ���ֵ��������ͨ��������������ֵΪָ��ͨ��������ֵ.
    hardquo:    �Ѷ�ϵ������ֵ��-10��20����ֵԽ�ߣ�˵���Ѷȸߣ����Խ����ࡣ������ʱ�򣬽�������С�ڻ���������-10,���齱��Ϊ0������maxexp������Ǳ�ܡ�
    PVPquo:    �Ƿ������VS������͵����񣬼������������ǣ����봫�ݸ�PVP�������ӳ�ϵ��(1-10)������Ϊ0.
    PVPlvl:    PVP�����������ȼ��������������񣺳ɹ�ɱ��3���Է����ˣ������ֵ����3���������ǡ�
    maxexp:    ���EXP��ֵ��������������EXP���������������ȡ���ֵ���ڼ���ӳɽ���֮ǰ��Ч��Ϊ0�����ơ�
    giver:    ˭���Ľ������������GIFT_D�������������
*/

//ȫ�ֶ����������ֵ����Ϊ200.
#define BASEEXP 100
//ȫ�ֶ���PVP��������������齱��Ϊ350.
#define PVPEXP 180

//ȫ�ֶ����޶����������EXP����Ϊ7500M
#define LIMITEXP 7500000000

//ȫ�ֶ���ת�����Ǳ�ܽ�����������Ϊ50000��
#define LIMITPOT 50000

//����VIP Player�Ľ����ӳ�ϵ����ע����㷽ʽΪ��exp + exp * VIP�����ӳ�ϵ�� / 10
#define VIPQUO 2

//������ս����ӳɲ�����ע����㷽ʽΪ��exp + exp * ���ռӳ�ϵ�� / 10 
#define FESTIVAL 1

//�����Խ�ɽׯ���뽱�������EXP���ơ�
#define ENTER_MIN_EXP 2000000

#include <ansi.h>;

int get_reward(object obj, string job, int shenflag, int potflag, int credit, int hardquo, int PVPquo, int PVPlvl, int maxexp, mixed giver)
{
    int exp, expquo, pot, shen,exprelife;
    string msg;

    msg = HIR"��ϲ�㣡��ɹ��������" + HIG + job + HIR + "�����㱻�����ˣ�\n" + NOR;

//�������PVP���ͣ���������齱��ȡȫ�ֶ��壬����ȡPVP��ֵ��
    if(!PVPquo){

//����ֵ����
        exp = BASEEXP;
        if(hardquo > 20) hardquo = 20;
        if(hardquo < -10) hardquo = -10;

        if(hardquo >= 0)
            exp = exp + exp * hardquo /10 + random(exp * hardquo /10);
        else
            exp = exp + exp * hardquo /10 - random( -1 * exp * hardquo /10);

        if(hardquo == -10)
            exp = 0;
    }
    else{

//���鲿��
        exp = PVPEXP;
        if(PVPquo > 10) PVPquo = 10;
        if(PVPquo < 0) PVPquo = 0;
        exp = exp + exp * PVPquo / 10 + random(50);  //������������־��飬����������Ӯ���μӵ��˶��С�
        exp = exp + (exp - PVPEXP) * PVPquo * PVPlvl;  //������⽱�����֣�Ҳ���ǻ��PVPlvlԽ�࣬����Խ�ࡣ
    }


//�鿴EXP�Ƿ񳬱�
        if(maxexp != 0 && exp > maxexp)
            exp = maxexp + random(maxexp/10);

//VIP player�ӳ�
        if(obj->query("vip/vip_time") - time() > 0)
            exp = exp + exp * VIPQUO / 10;

// ���ռӳɲ��֡�
            exp = exp + exp * FESTIVAL / 10;

//������ѧ�ľ����ȡ���֣����޵���20�㡣
        
        if(obj->query("relife/exp_ext"))                                     
        exp = exp + exp * (int)obj->query("relife/exp_ext",1) / 20;

// �޶����EXP�������޺󣬼���̶ȵؽ��;��齱����
        if(obj->query("combat_exp") > LIMITEXP){
            exp =  exp * 5 /100;
            tell_object(obj,"������Լ����������������ѧ���о��Ѿ������˾ٲ�Ω��ĳ̶ȣ��ƺ����ǽ�����˵�ġ�"+HIG+"��ѧ��"+NOR+"����\n");
        }

        msg += HIW + chinese_number(exp) + HIC + "��" + HIM + "����!\n"NOR;

        //Ǳ�ܲ���
        pot = exp / 2;

        if(hardquo == -10)
            pot = maxexp;

        msg += HIW + chinese_number(pot) + HIC + "��" + HIY + "Ǳ��!\n"NOR;

//shen����
        if(shenflag==1){
            shen = exp / 2 + random(exp / 6);
            msg += HIW + chinese_number(shen) + HIC + "������\n"NOR;
        }
        else if(shenflag == -1){
            shen = - exp / 2 - random(exp / 6);
            msg += HIW + chinese_number(-shen) + HIC + "��" + HIR + "����\n"NOR;
        }
		else if(shenflag == 2){
            shen = 3000 + random(100);
            msg += HIW + chinese_number(-shen) + HIC + "��" + HIR + "����\n"NOR;
        }
        else shen = 0;

//ͨ������
        if(credit < 0) credit = random(exp / 100);
        if(credit != 0) msg += HIW + chinese_number(credit) + HIC + "��" + HIW + "ͨ����\n"NOR;

//˫������
        expquo = 0;
        if(obj->query_condition("db_exp")){ 
        	 expquo = exp;
            msg += HIY + "���ھ�Ӣ֮������ã���о��ֶ���صõ���" + HIW + chinese_number(expquo) + HIC + "��" + HIM + "���飡\n"NOR;
        }
//������ѧEXP�ӳɵ�����
        if(obj->query("relife/exp_ext")) {
           exprelife=exp*(int)obj->query("relife/exp_ext",1) / 20;
           msg += HBYEL + "�㾲����������������ղŵ�������̣�������Ȼ���ʡ������صõ���" + HIW + chinese_number(exprelife) + HIC + "��" + HIM + "���飡\n\n"NOR;
                                          }
    obj->add("combat_exp",exp+expquo+expquo);
    obj->add("potential",pot);

    if(potflag != 1 && obj->query("potential") > obj->query("max_pot") && !obj->query("relife/times"))
      obj->set("potential",obj->query("max_pot"));

    if(obj->query("relife/times") && obj->query("potential") > LIMITPOT * (int)obj->query("relife/times"))
        obj->set("potential",LIMITPOT * (int)obj->query("relife/times"));
    obj->add("shen",shen);
    obj->add("SJ_Credit",credit);

    obj->add("job_time/"+job, 1);

    tell_object(obj,msg);


    if(random(500)<obj->query("kar") && !obj->query_temp("get_in_sjsz") && (int)obj->query("combat_exp",1)>ENTER_MIN_EXP)
    {
     
        tell_object(obj, HIW"��ͻȻ�����Լ��������д�ɣ���ȥ��˵�е�"HIR"�Խ�ɽׯ"HIW"����һ����\n"NOR);
        obj->set_temp("get_in_sjsz",1);
        log_file("jobreward/sjsz",sprintf("%s(%s)�ɹ���ɵ�%d��%s����ʱ��ý����Խ�ɽׯ����һ�Σ�"NOR,obj->name(),obj->query("id"),obj->query("job_time/"+job),job));
     }

    log_file( "jobreward/"+job,sprintf("%s(%s)�ɹ���ɵ�%d��%s����,��� EXP:%d, EXPQUO:%d, POT:%d, SHEN:%d, CREDIT:%d"NOR,obj->name(),obj->query("id"),obj->query("job_time/"+job),job,exp,expquo,pot,shen,credit));

    if(giver)
        GIFT_D->check_count(obj,giver,job,0);
    return 1;
}
