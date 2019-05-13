//
//  ToastOngate+Additional.h
//  ToastOngate
//
//  Created by NHNEnt on 24/01/2019.
//  Copyright © 2019 NHNEnt. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ToastOngate+SDK.h"

NS_ASSUME_NONNULL_BEGIN

@interface ToastOngate (Additional)

// 상품 구매
/**
 Purchase a product by only identifier. The purchase result is returned to the delegate.
 
 @param productIdentifier The product identifier to purchase
 */
+ (void)purchaseWithProductIdentifier:(NSString *)productIdentifier;


// 소모성 상품 소비
/**
 An additional API that allows Consume to be performed in the SDK.
 
 @param result The result of purchase
 @param completionHandler The handler to execute after consume
 */
+ (void)consumeWithPurchaseResult:(ToastOngatePurchaseResult *)result
                completionHandler:(nullable void (^)(NSError * _Nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END
