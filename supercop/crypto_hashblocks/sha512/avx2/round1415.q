    r1 += wc12131415[2]
      r6Sigma1 = r6>>>14
    ch1 = r0
      r618 = r6>>>18
    ch1 ^= r7
      r641 = r6>>>41
      r6Sigma1 ^= r618
    ch1 &= r6
      r2Sigma0 = r2>>>28
      r6Sigma1 ^= r641
    ch1 ^= r0
      r234 = r2>>>34
  maj0 = r3
  maj0 ^= r2
      r2Sigma0 ^= r234
    r1 += ch1
  r2andr3 = r3
      r239 = r2>>>39
  r2andr3 &= r2
      r2Sigma0 ^= r239
      r1 += r6Sigma1
  maj1 = r4
            r0 += wc12131415[3]
  maj1 &= maj0
  r5 += r1
      r1 += r2Sigma0
            ch0 = r7
  maj1 ^= r2andr3
            ch0 ^= r6
          r5Sigma1 = r5>>>14
  r1 += maj1
            ch0 &= r5
              r518 = r5>>>18
              r5Sigma1 ^= r518
          maj0 &= r1
            ch0 ^= r7
              r541 = r5>>>41
              r5Sigma1 ^= r541
              r1Sigma0 = r1>>>28
          maj0 ^= r2andr3
            r0 += ch0
              r0 += r5Sigma1
              r134 = r1>>>34
              r1Sigma0 ^= r134
          r4 += r0
          r0 += maj0
              r139 = r1>>>39
              r1Sigma0 ^= r139
              r0 += r1Sigma0
