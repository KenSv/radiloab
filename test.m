%deltaM =  0.403829;
%deltaA = -130.592245;
% ar =  [70   63   61   62   64   68   55   60   64   59   45   55   57   14   52   52   35   52   65   62   36   17   49   69   65   42   38   59   61   47   48   55 ...
%   41   40   53   36   33   52   69   68   44   54   56   29   51   54   50   18   37   67   79   72   70   57   43   39   29   60   70   67   54   55    5   60 ...
%   63   21   29   56   54   60   70   59   62   75   61   49   66   62   63   67   60   61   60   55   73   82   81   69   74   71   52   55   44   60   64   55 ...
%   49   73   75   65   56   65   47   56   82   83   50   69   73   65   44   53   70   67   32   66   74   70   64   50   27   65   76   76   76   75   77   81 ...
%   76   57   38   58   69   75   81   83   76   50   44   65   77   73   63   77   78   72   70   65   58   68   65   47   48   56   53   65   77   73   67   64 ...
%   66   70   65   61   43   45   60   71   64   63   57   46   66   69   71   73   52   55   60   58   69   72   74   81   76   56   60   75   75   67   55   45 ...
%   39   60   74   71   50   56   60   71   70   44   64   72   68   58   68   63   49   52   66   67   61   67   76   76   72   66   66   37   30   64   72   80 ...
%   75   30   63   69   64   65   78   71   42   67   42   59   77   79   74   70   63    0   53   61   48   31   39   52   65   70   54   61   62   48   71   75 ...
%   70   46   63   68   68   75   83   80   77   76   64   55   59   37   56   67   66   50   71   84   84   80   69   41   36   47   68   73   59   24   50   70 ...
%   76   77   82   80   64   68   76   70   53   67   70   61   41   64   70   73   77   68   51   66   64   65   74   82   85   71   26   59   60   53   49   76 ...
%   74   68   75   72   75   77   73   71   73   79   74   55   71   74   70   65   71   78   78   75   69   62   51   39   55   68   76   71   53   71   66   66 ...
%   71   61   75   75   60   49   31   60   71   74   78   77   75   66   66   71   68   61   54   59   68   62   62   62   59   65   60   66   56   34   64   68 ...
%   67   79   79   62   55   58   51   59   75   79   45   68   85   84   70   54   63   67   62   69   64   64   69   82   88   81   63   60   33   62   60   75 ...
%   82   71   58   71   75   33   59   66   74   48   42   55   72   75   58   51   68   53   72   75   61   80   75   41   72   76   58   70   67   61   62   72 ...
%   85   84   81   72   58   47   72   67   50   56   66   66   63   67   61   49   65   55   68   69   67   78   72   61   52   66   78   81   80   70   53   26 ...
%   61   83   83   60   73   58   58   44   65   77   80   70   50   55   60   57   50   59   64   78   85   84   73   77   76   74   79   70   76   55   86  -56 ...
%  -14   -1  -10  -47   74   63   78   77   43   75   63   77   79   80   77   92   94   83   69   72   69   65   29   46   66   77   80   78   81   83   76   51 ...
%   40   38   63   66   70   61   42   59   66   48   22   56   56   61   76   68   77   69   68   84   82   80   68   64   81   64   67   79   87   81   59   55 ...
%   75   77   69   68   34   68   80   79   68   52   28   72   82   81   69   53   50   53   25   61   63   65   20   68   71   41   55   62   64   82   82   80 ...
%   80   77   61   35   45   49   38   73   76   55   66   62   64   66   50   57   75   72   62   74   76   79   69   59   42   68   65   40   54   37   67   61 ...
%   44   63   62   63   55   64   52   67   81   86   82   69   44   54   72   58   31   59   66   70   75   55   63   73   52   54   64   57   53   44   46   41 ...
%   53   73   73   49   71   74   70   46   70   81   72   53   66   62   48   62   65   56   51   64   65   52   56   67   54   45   62   67   61   77   85   56 ...
%   74   78   76   75   71   67   64   45   68   62   47   65   61   50   77   79   69   60   56   51   24   65   75   72   66   68   69   67   52   49   52   64 ...
%   71   46   50   47   46   58   32   49   60   70   79   87   89   77   26   71   70   72   83   89   86   82   83   70   70   74   70   63   53   35   59   57 ...
%   65   71   69   60   37   41   55   63   67   76   72   65   73   73   63   53   55   69   71   61   52   72   77   72   63   76   83   73   64   67   66   69 ...
%   25   74   80   72   64   73   81   72   21   58   62   60   58   53   58   62   67   61   58   67   58   44   47   51   47   49   60   65   69   72   75   65 ...
%   39   66   67   67   68   64   58   46   42   49   79   85   71   51   77   78   66   67   56   69   73   73   77   75   56   53   48   52   60   66   72   76 ...
%   79   70   68   66   71   72   67   73   78   65   55   70   66   53   61   72   77   71   59   64   31   40   51   60   83   94   88   68   62   66   64   37 ...
%   65   77   75   74   75   65   36   34   26   36   23   55   68   64   64   68   63   71   66   62   63   61   57   62   75   74   74   81   81   84   83   56 ...
%   55   47   63   41   63   66   72   68   39   73   75   75   79   76   73   70   74   81   73   48   46   65   59   39   49   67   69   59   61   35   59   67 ...
%   59   60   22   65   74   78   76   52   55   61   52   24   64   74   72   33   60   53   41   43   35   50   55   55   58   53   60   65   57   31   52   38 ...
%   49   58   51   41   50   68   61   22   35   38   55   48   31   45   53   53   50   24   57   50   53   54   43   66   63   60   70   67   55   42   57   68];

%out2
% deltaM = 0.372180;
% deltaA = -134.992169;
% ar = [113  106   88  106  104   75   97  111  113   92   50   70   76  104  110  107  119  127  125  111  102   90   88  105  108  117  116  104   56   83   91  109... 
%  107   90  104  104   82  114  113   90   59   84  110  120  117  108  100  115  106   89  102   95   91   99   98  106  106  113  118  120  107  108   99   94... 
%  107   99   92  106  122  123  106  101   97   91   99   81  103  112   86   89   67   90   82   87  103  108   97  115   87  107  113  103   46  109  110  112... 
%  116  121  114   91  100  116  118   97   67   90  101  100   84  102  110  102   92   81   84  108  112  114  121  123  110   67   94   90  111  112  100   88... 
%   95  104   92   99  114  115  111  102   99  105  102   92   78  100   97  117  115   96  111   81  115  122  120  107   98  111  121  118   99   80   92  102... 
%  112  124  122   94   95   93   87   90   91  104  110  111  124  115   76  101   93  110  118  116  110  104  109  119  122  117  115  113  111  121  102   80... 
%   82  106  105   89   71   74  108  113  102   91   99   87  101   84   94  100   98   55   97  102   78   99  105  107  119  120  113  114  110  110  103  108... 
%  111   99   76  104  119  115  112  103  101  114  101   72   85  103   99   92  105   70  107   82  120  126  109   74  101  104   82   89   79   63   90  103...
%  101  115  121  116  108  104   86  105  104   64  101  101  110  108  108  109  111   93  100  106   93   58   88  108   98   82   80   93   53   97   88  119... 
%  119  114   93   77   94  105  109   96   89   98   96   94   88  109  110  120  126  122  116  118  114  110  111  103  105   93   88  104  117  119  112  101... 
%   90   91   91   90  106  115  111   88   61   78   87  100  100   88   96  101   95   94  105  107  107  106   88  105   97  101   93  104  113  106   92   89... 
%  105  116  103   58  104  102   83   67   78   75   99  112  112  110  113  107   82  106  111   72  115  114   84  100  105   86   92  109  118  114  101  108... 
%  107  115  122  120  108  103  107  107   96   97  116  111   93  113  115  104   95  105  105  105  108   99  127  -88  -41  -14   -7  -14  -29  -36  -38  -25... 
%  -11   -4   -1   -1  -10  -30  -27  -24  -34  -37  -47  -34  -32  -33  -32  -29  -47  -19  -12  -18  -20  -14  -20  -31  -31  -23  -19  -24  -30  -52  -42  -35... 
%  -35  -55  -69 -117  -60  -52  -32  -16  -35  -17   -3   -4  -11  -21  -26  -30  -18  -11  -23  -43  -52  -37  -23  -17  -19  -24  -27  -62  -26  -13  -14  -31... 
%  -26  -24  -26  -48  -94   85  127  113   70   96  104   91  107  117  122  115   98  120  124  114   55   66   99  101  104  118  121  126  123  108  112  113... 
%   99   71   79   41   71   80   79   93   95   75  106   90  102   97  108   97   98  109  110  109   96   96   89   92   60   68   96  109   97   81   91   87... 
%  105  113  112   98   97  110  122  127  120  104   87   87  106  124  123  105   63   82   32  100   94  116  120  104  103  119  127  121  108  102  102   57... 
%   84   96  110   99   92   98   92  105  115  108  105  107   94   66   65   89   92  103   89  104  116  111  107  108  108   96   70   92  102  102   83   88... 
%  114  116  104   80   85  106  106   83  104  108   83   86  103  105  104  108   95   77   90  119  123  106   87  105  105  105  113  105   93   82  101  107... 
%  105   99   88   79   73  114  124  105  113  116  103   80   83  109  112   99   84   98   92   83   87  108  102   93   82   65   78   70   85   62   92   81... 
%   83   90  104  109  110  108  115  109   61   81   98   90   86   89  104  106   68   92   71   85   89    0  101  100   96   98  101   87   83  100   99  104... 
%   86   79  108  109   99   70   94  105   88  101  111   93   92  103  107  122  111   88   83   95  108  101   97  112];

%out3
% deltaM = 0.404886;
% deltaA = -130.430908;
% ar = [96   93   82   55   77   75   52   77   81   56   78   93   97   92   79   62   83   90   84   84   82   71   86   76   86   65   77   75   78   98   96   88... 
%   60   82   84   92   95   92   77   64   85   96   91   81   90   88   67   97   97   76   56   70   75   76   67   84   85   77   82   74   46   44   74   81... 
%   72   74   72   46   85   99   94   79   77   85   83   71   52   77   85   60   87   90   68   62   67   80   94   97   88   88   88   87   82   76   85   85... 
%   77   48   73   69   78   78   61   94   96   78   77   84   79   82   79   66   77   76   88   78   85   61   91   88   90   94   83   77   58   52   70   79... 
%   56   80   78   73   57   65   76   76   76  100   97   89   80   82   85   84   83   83   86   74   64   74   79   91   87   87   87   81   71   71   89   78... 
%   54   86   98   85   91   91   52   82   87   92   98   94   67   87  103  102   77   64   85   93   81   46   71   93   98   87   72   70   66   63   84   87... 
%   84   74   80   87   87   91   86   84   93   89   86   92   98   93   71   80   95   88   74   68   94   96   94   94   80   90   94   86   83   87   89   86... 
%   85   92   88   87   87   58   69   81   93   88    0   76   95  104   96   75   71   73   81   91   80   59   41   30   65   87   96   99   95   95   84   82... 
%   83   33   84   83   73   62   75   80   88   85   81   67   72   88   79  -49  -11   -1  -13  -54   66   85   74   59   73   66   66   28   78   90   93   98... 
%  102   97   93   86   91   97   90   79   78   97   89   64   35   71   83   88   92   93   96   98   89   52   63   65   73   80   59   90   89   87   81   16... 
%   80   81   76   88   94   90   91   90   71   54   72   87   91   81   81   85   81   83   94   95   61   82   84   69   59   88   98   92   90   94   76   71... 
%   76   73   75   74   74   84   86   89   88   82   54   79   88   89   94   90   83   78   86   77   70   91   93   80   59   82   94   88   82   86   83   89... 
%   89   82   98   94   85   69   73   95   90   76   93   96   79   76   72   52   78   91   89   84   87   90   87   77   55   59   66   77   99  104  114   98... 
% -116  -45  -18  -16  -37  -96   83   98   97   78   80   67   65   77   89   96   86   91   96   89   84   85   62   80   94  103   97   68   97   94   86   96... 
%   96   86   66   71   87   85   81   85   86   87   89   66   66   92   98   91   83   81   85   93   71   95  100   89   89   94   66   82   77   73   87   85... 
%   74   65   76   83   86   81   78   92   91   86   68   86   89   72   81   64   70   71   94   95   95   70   93   87   76   86   90   91   69   70   54   78... 
%   86   77   44   49   82   59   97  106   96   67   60   75   83   85   76   77   99  100   97   98   92   82   85   96   97   87   88   91   96   84   59   79... 
%   81   67   49   82   89   88   85   97  104  103   93   96   98   55   77  106   90   98  -70  -21   -4  -10  -42  119  100   90   91   90   78   95   81   88... 
%   77   93   90   52   56   64   57   42   72   73   49   84   91   95   92   91   95   91   82   77   86   84   85   88   78   44   81   96   99  101   98   89... 
%   78   79   84   80   57   73   84   81   69   59   62   72   66   79   86   91   90   84   82   85   89   89   81   67   57   77   72   70   72   76   85   95... 
%   98   93   91   91   91   94   94   81   77   79   66   58   57   66   54   72   92   95   85   88   96   92   84   70   86   85   75   82   78   82   84   90... 
%   82   74   86   91   81   73   64   70   36   82   89   74   76   83   82   76   78   84   92   95   86   66   80   80   80   87  100   97   83   78   88   99... 
%   96  100   86   96  -47  -12   -4  -18  -63   65   90   86   85   92  107   98   89   87  100   97   79   66   64   79];  

%out4
% deltaM = 0.365557;
% deltaA = -120.910967;
% ar = [82   75   73   82   84   65   60   71   75   78   75   81   80   67   52   57   52   67   84   92   82   59   54   66   73   63   69   74   74   65   29   48... 
%   50   47   30   26   59   73   63    6   56   62   63   62   60   44   38   44   44   60   63   33    1   24   52   66   69   66   68   51   40   58   63   53... 
%   63   73   69   67   78   83   78   65   69   71   61   48   26   29   67   84   78   35   71   73   71   67   50   39   68   67   60   67   63   63   61   55... 
%   74   78   73   67   75   79   79   65   65   72   56   38   72   63   58   72   64   32   71   74   71   77   82   75   45   58   32   67   70   38   61   65... 
%   51   62   39   58   75   71   63   74   75   64   39   45   63   73   66   76   79   67   55   80   81   62   81   86   86   87   81   63   76   76   57   47... 
%   75   78   65   60   74   70   67   59   41   39   52   39   74   71   76   78   62   48   66   67   66   64   38   56   51   26   52   46   56   57   41   74... 
%   84   83   81   74   40   74   67   57   67   52   67   78   71   62   70   66   65   72   69   82   82   63   55   77   74   59   48   72   66   57   67   73... 
%   49   65   70   59   79   85   83   80   85   89   89   82   69   56   68   61   48   67   57   71   79   81   82   74   48   58   76   86   83   76   80   75... 
%   63   23   60   63   66   72   70   63   76   80   44   65   52   55   62   75   66   59   67   58   33   49   60   66   78   80   66   57   37   41   52   64... 
%   62    2   63   76   78   72   64   66   72   68   48   19   52   59   60   75   71   37   57   39   44   70   70   59   31   60   69   22   64   58   35   38... 
%   42   72   77   82   89   85   56   32   45   60   66   58   67   71   68   60   67   76   74   70   72   64   75   70   45   50   64   65   70   79   78   67... 
%   76   70   48   47   59   47   24   41   64   75   65   61   55   52   62   73   62   38   80   67   37   61   42   61   71   69   76   77   91   92 -123  -35... 
%   -5   -1  -22  -83  100   89   69   94   51   71    7   36   59   47   68   71   71   80   67   71   75   59   45   65   51   66   63   64   63   57   71   57... 
%   64   54   57   75   69   48   47   39   70   82   78   84   82   69   64   68   75   82   80   67   59   70   69   75   79   75   61   60   67   66   64   13... 
%   79   93   90   83   82   72   54   65   76   85   80   47   32    0   61   33   64   67   60   62   73   78   57   75   87   76   45   57   62   53   66   66... 
%   65   71   71   71   69   54   38   67   79   77   68   61   54   50   50   37   59   76   84   74   78   78   67   44   46   65   66   73   75   62   71   82... 
%   70   54   57   52   74   77   79   76   64   58   49   63   57   37   71   61   60   74   64   73   76   71   74   73   70   66   71   76   72   74   75   77... 
%   82   79   48   73   79   74   82   78   65   85   81   54   50   41   51   65   67   66   74   70   29   71   86   82   73   67   48   66   74   57   63   71... 
%   73   66   42   68   54   27   30   64   71   58   50   65   71   69   66   66   54   36   55   68   78   83   62   24   73   85   83   65   74   78   62   81... 
%   79   41   56   71   66   71   83   72   13   44   40   60   77   71   48   75   68   76   64   49   62   57   68   39   55   62   53   77   75   61   64   72... 
%   62    5   54   74   82   79   75   68   66   59   74   85   72   69   37   55   60   51   53   71   75   71   76   83   77   53   50   56   49   59   69   74... 
%   78   73   76   70   51   56   73   69   40   70   39   55   57   52   68   76   71   69   70   40   53   48   71   76   81   67   40   64   71   57   72   75... 
%   61   40   76   80   68   57   57   74   48   35   15   41   64   70   55   46   42   55   69   79   74   67   68   58];

%out5
deltaM = 0.416817;
deltaA = -123.831491;
ar = [71   64   74   75   60   38   51   65   64   58   66   78   81   74   76   68   67   61   51   56   70   77   76   66   71   62   68   72   54   51   64   68... 
  19   77   86   86   70   55   64   62   45   70   80   73   63   80   83   56   78   81   65   55   56   55   68   79   80   65   53   60   66   43   71   80... 
  84   87   83   72   63   53   52   53   45   37   43   42   45   54   62   63   77   75   53   71   62   65   75   75   67   74   83   83   82   81   79   75... 
  73   66   67   64   76   75   63   45   34   48   15   64   79   80   75   71   53   66   72   72   74   56   65   78   68   61   62  115 -116 -110 -121   99... 
  73   64   33   63   66   61   55   47   70   68   61   57   60   66   64   67   48   54   57   68   67   80   78   50   79 -103  -62  -48  -54  -81  100   72... 
  80   60   55   64   63   73   70   73   72   77   55   17   66   66   80   57   82   78   86   98   98  117  115  -95  -27   -2   -1  -22  -80  116  115  105... 
  99   83   94   47   75    2   84   73   72   32   65   62   74   67   75   47   40   73   75   84   50   71  -86  -56  -48  -60  -96   72   75   67   63   43... 
  53   64   71   71   66   62   64   42   63   72   68   46   62   38   45   62   53   77   65   59   91 -123 -110 -114  118   45   70   58   48   55   47   54... 
  58   56   60   55   48   70   71   63   57   63   65   65   60   57   50   74   80   73   64   72   75   79   75   71   68   56   33   53   58   63   39   59... 
  60   46   64   55    3   55   59   45   63   64   51   27   19   50   67   75   83   84   75   62   65   77   81   73   62   65   67   59   32   66   63   51... 
  64   61   47   52   56   75   78   64   50   22   45   53   67   75   39   67   66   58   62   81   90   82   44   28   48   37   66   59   46   38   58   63... 
  32   59   59   66   61   42   71   72   58   64   70   61   25   36   44   52    7   53   62   70   65   66   54   46   62   68   56   65   67   55   51   64... 
  61   56   56   70   75   74   74   70   64   72   71   51   46   68   73   75   78   67   48   57   46   53   38   44   39   50   70   67   63   57   46   64... 
  81   83   73   56   50   58   56   58   68   59   53   70   54   62   67   57   68   76   73   80   87   85   60   78   83   82   75   67   72   62   38   56... 
  60   50   67   63   25   62   64   52   78   75   62   56   60   66   67   72   76   78   71   30   52   66   73   79   75   59   53   73   76   34   59   28... 
  66   66   57   42   65   70   65   51   36   46   25   70   74   67   68   66   63   67   57   58   80   84   65   56   52   63   65   50   47   67   67   72... 
  77   73   63   66   48   32   66   82   82   74   70   65   57   61   61   38   64   66   50   60   76   83   82   67    4   44   50   36   50   61   48   60... 
  71   44   70   75   68   56   67   76   72   62   22   62   59   61   61   23   64   57    0   63   61   67   73   66   58   54   53   66   35   70   70   59... 
  68   70   55   38   70   66    5   37   55   63   63   66   78   74   60   64   61   59   60   62   63   73   74   79   81   71   58   65   54   66   60   72... 
  75   70   68   74   65   71   71   59   58   68   76   66   50   63   72   76   74   47   57   76   83   78   68   71   52   38   52   57   54   55   43   37... 
  50   53   67   74   74   71   66   67   59   15   65   70   72   80   66   66   72   67   66   57   40   42   45   55   64   82   84   70   54   30   54   55... 
  67   70   52   35   65   73   66   66   50   52   51   41   58   48   53   57   70   39   68   74   82   79   65   68   67   66   66   66   48   37   52   61... 
  75   68   53   65   53   37   60   74   71   68   67   61   54   52   70   83   83   68   15   43   46   64   51   55];
  
  
%y = exp(-ar/100);
%y = exp(-(ar * deltaM + deltaA));
%y = power(10, -ar/100);
y = power(10, (ar * deltaM + deltaA)/10);
plot(y);

dmin = 1000;
dmax = 0;
middle = 0;
koef = linspace(0, 0, arSize);


for n = 1:2
    for i= 1:(arSize-1)
        delta = y(i+1) - y(i);
        if (abs(delta) > dmax) 
%            dmax = y(i+1);
            dmax = delta;
        end  
%         if (abs(delta) < dmin) 
%             dmin = delta;  
%         end  
        koef(i+1) = delta;
    end

    for i= 2:arSize
        y(i) = y(i) * y(i) / dmax;
    end
end 


%{
%%for n = 1:2
%  for i= 2:arSize
%%    if (sign(koef(i)))
%%      y(i) = y(i-1) + abs(koef(i)) * (koef(i) / dmax);
%%      d = abs(koef(i)) * (koef(i) / dmax);
%      if (koef(i) < (dmax * 0.8))
%        y(i) = y(i-1) + abs(koef(i)) * (koef(i) / dmax);
%      endif  
%%      y(i) = y(i) - abs(koef(i)) * (koef(i) / dmax);
%%      y(i-1) = y(i-1) + abs(koef(i-1)) * (koef(i-1) / dmax);
%%      y(i) = y(i-1) + d;
%%      y(i-1) = y(i-1) - d;
%%    endif
%  end
%%endfor
%}



%plot(y);