<?php
/**
 * @file
 * Contains implementation of a page to charge the card for Stripe Checkout
 */

function stripe_checkout_charge() {
  if (isset($_POST['stripeToken'])) { $token = $_POST['stripeToken']; }
  
  if (!empty($token)) {
    $tokentype = $_POST['stripeTokenType'];
    $email = $_POST['stripeEmail'];
    $amount = check_plain(($_POST['data-amount'])*100);
    $_SESSION['stripe_checkout_amount_cents'] = $amount;
    
    $config = config('stripe_checkout.settings');
    
    if (module_exists('libraries') && ($stripe_php = libraries_load('stripe_php')) && !empty($stripe_php['loaded'])) {
    } else {
      $stripe_php = NULL;
      backdrop_set_message(t('The Stripe Checkout settings are not correct and we are unable to charge the card. Please alert the system administrator.'),'error');
      return "<p>There was an error.</p>";
    }
   
    $mode = $config->get('stripe_checkout-mode');
    if ($mode) {
      $key = $config->get('stripe_checkout-live-secret-key');
    } else {
      $key = $config->get('stripe_checkout-test-secret-key');
    }
  
    \Stripe\Stripe::setApiKey($key);
    
    // Create the charge on Stripe's servers - this will charge the user's card
    try {
      $charge = \Stripe\Charge::create(array(
        "amount" => $amount, 
        "currency" => $config->get('stripe_checkout-currency'),
        "source" => $token,
        "description" => $config->get('stripe_checkout-description')
        ));
    } catch(\Stripe\Error\Card $e) {
      // The card has been declined
      backdrop_set_message(t("Your card has been declined."),'error');
      backdrop_set_message($e,'error');
    }
    return "<p>We have attempted to charge your card. Thank you for your support!</p>";
  } else {
    return "<p>No donation information has been provided. Please try again.</p>";
  }


}
