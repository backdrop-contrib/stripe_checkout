<?php
/**
 * @file
 * Contains implementation of admin settings form for Stripe Checkout
 */

/**
 * Admin form to set up the Stripe Checkout configuration.
 */
 
function stripe_checkout_admin_form() {
  $form = array();
  $config = config('stripe_checkout.settings');

  $form['stripe_checkout-donateblock-enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Stripe Checkout Donate Block'),
    '#default_value' => $config->get('stripe_checkout-donateblock-enabled'),
  );
  
  $form['stripe_checkout-donateblock-settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Stripe Checkout Donate Block Settings'),
    '#description' => t("Configure the Stripe Checkout donation block settings here."),
    '#collapsible' => TRUE,
    '#collapsed' => 0,
    '#states' => array(
      'visible' => array(
        ':input[name="stripe_checkout-donateblock-enabled"]' => array('checked' => TRUE),
      ),
      'invisible' => array(
        ':input[name="stripe_checkout-donateblock-enabled"]' => array('checked' => FALSE),
      ),
    ),
  );

  $form['stripe_checkout-donateblock-settings']['stripe_checkout-image'] = array(
    '#title' => t('Logo or Image'),
    '#type' => 'managed_file',
    '#description' => t('The uploaded logo/image will be displayed on the checkout form. Accepted formats: jpg gif png. Minimum size recommended is 128x128px. (Defaults to site\'s logo if left blank).'),
    '#default_value' => $config->get('stripe_checkout-image'),
    '#upload_location' => 'public://stripe_checkout_image/',
    '#upload_validators' => array(
      'file_validate_extensions' => array('gif png jpg jpeg'),
    ),
  );

  $form['stripe_checkout-donateblock-settings']['stripe_checkout-name'] = array(
    '#type' => 'textfield',
    '#title' => t('Site or Account Name'),
    '#description' => t('Enter the name of your Organization or Website. (Defaults to your website name if left blank).'),
    '#default_value' => $config->get('stripe_checkout-name'),
  );

  $form['stripe_checkout-donateblock-settings']['stripe_checkout-description'] = array(
    '#type' => 'textfield',
    '#title' => t('Description'),
    '#description' => t('Enter the description of what the donation will be used for or what they are donating towards.'),
    '#default_value' => $config->get('stripe_checkout-description'),
  );
  
  $form['stripe_checkout-donateblock-settings']['stripe_checkout-amount'] = array(
    '#type' => 'textfield',
    '#title' => t('Default amount'),
    '#description' => t('Enter the default amount that should show in the amount field, in cents. (2000 = $20).'),
    '#default_value' => $config->get('stripe_checkout-amount'),
  );
  
  $form['stripe_checkout-donateblock-settings']['stripe_checkout-currency'] = array(
    '#type' => 'select',
    '#title' => t('Currency'),
    '#description' => t('Enter the currency. NOTE: With few exceptions, Stripe\'s policy states, "Bank accounts must be located in the country where their currency is based–for example, USD banks accounts must be based in the United States..." (<a href="https://support.stripe.com/questions/which-currencies-does-stripe-support">Read more</a>) Defaults to USD.'),
    '#options' => array(
      'USD' => 'USD',
      'CAD' => 'CAD',
      'GBP' => 'GBP',
    ),
    '#default_value' => $config->get('stripe_checkout-currency'),
  );
  
  $form['stripe_checkout-donateblock-settings']['stripe_checkout-zip'] = array(
    '#type' => 'checkbox',
    '#title' => t('Require Zip Code'),
    '#default_value' => $config->get('stripe_checkout-zip'),
  );

  $form['stripe_checkout-donateblock-settings']['stripe_checkout-billing-addr'] = array(
    '#type' => 'checkbox',
    '#title' => t('Require Billing Address'),
    '#default_value' => $config->get('stripe_checkout-billing-addr'),
  );

  $form['stripe_checkout-donateblock-settings']['stripe_checkout-shipping-addr'] = array(
    '#type' => 'checkbox',
    '#title' => t('Require Shipping Address'),
    '#default_value' => $config->get('stripe_checkout-shipping-addr'),
  );

  $form['stripe_checkout-donateblock-settings']['stripe_checkout-outer-button'] = array(
    '#type' => 'textfield',
    '#title' => t('Outer/Initial Button Text'),
    '#description' => t('Enter the text to show on the first button. Default: <strong>Donate now.</strong>'),
    '#default_value' => $config->get('stripe_checkout-outer-button'),
  );
  
  $form['stripe_checkout-donateblock-settings']['stripe_checkout-inner-button'] = array(
    '#type' => 'textfield',
    '#title' => t('Inner/Submit Button Text'),
    '#description' => t('Enter the text to show on the inner/submit button. Default: <strong>Donate {{amount}}.</strong>'),
    '#default_value' => $config->get('stripe_checkout-inner-button'),
  );

  $form['stripe_checkout-donateblock-settings']['stripe_checkout-prefill-email'] = array(
    '#type' => 'checkbox',
    '#title' => t('Prefill email address'),
    '#description' => t('If the user is logged in, should we prefill the email address from their Backdrop account?'),
    '#default_value' => $config->get('stripe_checkout-prefill-email'),
  );

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  
  return $form;
}

/**
 * Validation callback for stripe_checkout_admin_form().
 */
function stripe_checkout_admin_form_validate($form, &$form_state) {
  $name = 'stripe_checkout-amount' ;
  if (!empty($form_state['values'][$name]) && !is_numeric($form_state['values'][$name])) {
    form_set_error($name, t('The default amount has to be a number.'));
  }
}

/**
 * Submit handler for stripe_checkout_admin_form().
 */
function stripe_checkout_admin_form_submit($form, &$form_state) {
  $config = config('stripe_checkout.settings');
  $values = $form_state['values'];

  if (isset($values['stripe_checkout-image']) && $values['stripe_checkout-image']) {
    $file = file_load($values['stripe_checkout-image']);
    $file->status = FILE_STATUS_PERMANENT;
    file_save($file);
    file_usage_add($file, 'stripe_checkout', 'Stripe Checkout Config', $values['stripe_checkout-image']);
  }
  $config->set('stripe_checkout-donateblock-enabled' , $values['stripe_checkout-donateblock-enabled']);
  $config->set('stripe_checkout-image' , $values['stripe_checkout-image']);
  $config->set('stripe_checkout-currency' , $values['stripe_checkout-currency']);
  $config->set('stripe_checkout-zip' , (bool)$values['stripe_checkout-zip']);
  $config->set('stripe_checkout-billing-addr' , (bool)$values['stripe_checkout-billing-addr']);
  $config->set('stripe_checkout-shipping-addr' , (bool)$values['stripe_checkout-shipping-addr']);
  $config->set('stripe_checkout-prefill-email' , (bool)$values['stripe_checkout-prefill-email']);
  $config->set('stripe_checkout-outer-button' , $values['stripe_checkout-outer-button']);
  $config->set('stripe_checkout-inner-button' , $values['stripe_checkout-inner-button']);
  $config->set('stripe_checkout-name' , $values['stripe_checkout-name']);
  $config->set('stripe_checkout-description' , $values['stripe_checkout-description']);
  $config->set('stripe_checkout-amount' , intval($values['stripe_checkout-amount']));
  $config->save();

  backdrop_set_message(t('Stripe Checkout settings have been saved.'));
}






