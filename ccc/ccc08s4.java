import java.io.*;
import java.util.*;
public class Ccc08s4 {

    static ArrayList<Integer>Sums;
    public static int tf(int a, int b, int c, int d) {
        Sums.clear();
        int[]A={a, b, c, d};
        calc(A, 4);
        int max=0;
        for(int sum:Sums) {
            if(sum>max&&sum<=24) {
                max=sum;
            }
        }
        return max;
    }
    
    public static void calc(int[]A, int index) {
        if(index==1) {
            for(int a:A) {
                if(a!=Integer.MIN_VALUE) {
                    Sums.add(a);
                    break;
                }
            }
        }else {
            for(int i=0;i<A.length;i++) {
                for(int j=0;j<A.length;j++) {
                    if(i!=j&&A[i]!=Integer.MIN_VALUE&&A[j]!=Integer.MIN_VALUE) {
                        int temp1=A[i];
                        int temp2=A[j];
                        A[i]=temp1+temp2;
                        A[j]=Integer.MIN_VALUE;
                        calc(A, index-1);
                        A[i]=temp1-temp2;
                        calc(A, index-1);
                        A[i]=temp1*temp2;
                        calc(A, index-1);
                        if(temp2!=0&&temp1%temp2==0) {
                            A[i]=temp1/temp2;
                            calc(A, index-1);
                        }
                        A[i]=temp1;
                        A[j]=temp2;
                    }
                }
            }
        }
    }
    public static void main(String[] args) throws IOException {
        BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
        Sums=new ArrayList<>();
        int N=Integer.parseInt(br.readLine());
        for(int i=0, a, b, c, d;i<N;i++) {
            a=Integer.parseInt(br.readLine());
            b=Integer.parseInt(br.readLine());
            c=Integer.parseInt(br.readLine());
            d=Integer.parseInt(br.readLine());
            System.out.println(tf(a, b, c, d));
        }
    }
    
}
