    r7 += wc891011[0]
      r4Sigma1 = r4>>>14
    ch7 = r6
      r418 = r4>>>18
    ch7 ^= r5
      r441 = r4>>>41
      r4Sigma1 ^= r418
    ch7 &= r4
      r0Sigma0 = r0>>>28
      r4Sigma1 ^= r441
    ch7 ^= r6
      r034 = r0>>>34
  maj6 = r1
  maj6 ^= r0
      r0Sigma0 ^= r034
    r7 += ch7
  r0andr1 = r1
      r039 = r0>>>39
  r0andr1 &= r0
      r0Sigma0 ^= r039
      r7 += r4Sigma1
  maj7 = r2
            r6 += wc891011[1]
  maj7 &= maj6
  r3 += r7
      r7 += r0Sigma0
            ch6 = r5
  maj7 ^= r0andr1
            ch6 ^= r4
          r3Sigma1 = r3>>>14
  r7 += maj7
            ch6 &= r3
              r318 = r3>>>18
              r3Sigma1 ^= r318
          maj6 &= r7
            ch6 ^= r5
              r341 = r3>>>41
              r3Sigma1 ^= r341
              r7Sigma0 = r7>>>28
          maj6 ^= r0andr1
            r6 += ch6
              r6 += r3Sigma1
              r734 = r7>>>34
              r7Sigma0 ^= r734
          r2 += r6
          r6 += maj6
              r739 = r7>>>39
              r7Sigma0 ^= r739
              r6 += r7Sigma0
