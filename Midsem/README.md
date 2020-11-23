Input for rectangle : (100,150) (300,150) (300,250) (100,250)

Rotation : by 90 degrees about the centre

Scaling : Uniform scaling by 1.5 in x direction and 1.5 by y direction

Conclusion : Composition of transformations is same as transforming multiple times.

Method 1: Calculate p1 = T 1 ∗ p, p2 = T 2 ∗ p1 , p3 = T 3 ∗ p2

Method 2: Calculate T = T 1 ∗ T 2 ∗ T 3 , then p3 = T ∗ p.

Both produce same results
